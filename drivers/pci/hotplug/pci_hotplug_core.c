<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI HotPlug Controller Core
 *
 * Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001-2002 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <kristen.c.accardi@पूर्णांकel.com>
 *
 * Authors:
 *   Greg Kroah-Harपंचांगan <greg@kroah.com>
 *   Scott Murray <scotपंचांग@somanetworks.com>
 */

#समावेश <linux/module.h>	/* try_module_get & module_put */
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/uaccess.h>
#समावेश "../pci.h"
#समावेश "cpci_hotplug.h"

#घोषणा MY_NAME	"pci_hotplug"

#घोषणा dbg(fmt, arg...) करो अणु अगर (debug) prपूर्णांकk(KERN_DEBUG "%s: %s: " fmt, MY_NAME, __func__, ## arg); पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)

/* local variables */
अटल bool debug;

अटल LIST_HEAD(pci_hotplug_slot_list);
अटल DEFINE_MUTEX(pci_hp_mutex);

/* Weee, fun with macros... */
#घोषणा GET_STATUS(name, type)	\
अटल पूर्णांक get_##name(काष्ठा hotplug_slot *slot, type *value)		\
अणु									\
	स्थिर काष्ठा hotplug_slot_ops *ops = slot->ops;			\
	पूर्णांक retval = 0;							\
	अगर (!try_module_get(slot->owner))				\
		वापस -ENODEV;						\
	अगर (ops->get_##name)						\
		retval = ops->get_##name(slot, value);			\
	module_put(slot->owner);					\
	वापस retval;							\
पूर्ण

GET_STATUS(घातer_status, u8)
GET_STATUS(attention_status, u8)
GET_STATUS(latch_status, u8)
GET_STATUS(adapter_status, u8)

अटल sमाप_प्रकार घातer_पढ़ो_file(काष्ठा pci_slot *pci_slot, अक्षर *buf)
अणु
	पूर्णांक retval;
	u8 value;

	retval = get_घातer_status(pci_slot->hotplug, &value);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार घातer_ग_लिखो_file(काष्ठा pci_slot *pci_slot, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;
	अचिन्हित दीर्घ lघातer;
	u8 घातer;
	पूर्णांक retval = 0;

	lघातer = simple_म_से_अदीर्घ(buf, शून्य, 10);
	घातer = (u8)(lघातer & 0xff);
	dbg("power = %d\n", घातer);

	अगर (!try_module_get(slot->owner)) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	चयन (घातer) अणु
	हाल 0:
		अगर (slot->ops->disable_slot)
			retval = slot->ops->disable_slot(slot);
		अवरोध;

	हाल 1:
		अगर (slot->ops->enable_slot)
			retval = slot->ops->enable_slot(slot);
		अवरोध;

	शेष:
		err("Illegal value specified for power\n");
		retval = -EINVAL;
	पूर्ण
	module_put(slot->owner);

निकास:
	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण

अटल काष्ठा pci_slot_attribute hotplug_slot_attr_घातer = अणु
	.attr = अणु.name = "power", .mode = S_IFREG | S_IRUGO | S_IWUSRपूर्ण,
	.show = घातer_पढ़ो_file,
	.store = घातer_ग_लिखो_file
पूर्ण;

अटल sमाप_प्रकार attention_पढ़ो_file(काष्ठा pci_slot *pci_slot, अक्षर *buf)
अणु
	पूर्णांक retval;
	u8 value;

	retval = get_attention_status(pci_slot->hotplug, &value);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार attention_ग_लिखो_file(काष्ठा pci_slot *pci_slot, स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;
	स्थिर काष्ठा hotplug_slot_ops *ops = slot->ops;
	अचिन्हित दीर्घ lattention;
	u8 attention;
	पूर्णांक retval = 0;

	lattention = simple_म_से_अदीर्घ(buf, शून्य, 10);
	attention = (u8)(lattention & 0xff);
	dbg(" - attention = %d\n", attention);

	अगर (!try_module_get(slot->owner)) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	अगर (ops->set_attention_status)
		retval = ops->set_attention_status(slot, attention);
	module_put(slot->owner);

निकास:
	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण

अटल काष्ठा pci_slot_attribute hotplug_slot_attr_attention = अणु
	.attr = अणु.name = "attention", .mode = S_IFREG | S_IRUGO | S_IWUSRपूर्ण,
	.show = attention_पढ़ो_file,
	.store = attention_ग_लिखो_file
पूर्ण;

अटल sमाप_प्रकार latch_पढ़ो_file(काष्ठा pci_slot *pci_slot, अक्षर *buf)
अणु
	पूर्णांक retval;
	u8 value;

	retval = get_latch_status(pci_slot->hotplug, &value);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल काष्ठा pci_slot_attribute hotplug_slot_attr_latch = अणु
	.attr = अणु.name = "latch", .mode = S_IFREG | S_IRUGOपूर्ण,
	.show = latch_पढ़ो_file,
पूर्ण;

अटल sमाप_प्रकार presence_पढ़ो_file(काष्ठा pci_slot *pci_slot, अक्षर *buf)
अणु
	पूर्णांक retval;
	u8 value;

	retval = get_adapter_status(pci_slot->hotplug, &value);
	अगर (retval)
		वापस retval;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल काष्ठा pci_slot_attribute hotplug_slot_attr_presence = अणु
	.attr = अणु.name = "adapter", .mode = S_IFREG | S_IRUGOपूर्ण,
	.show = presence_पढ़ो_file,
पूर्ण;

अटल sमाप_प्रकार test_ग_लिखो_file(काष्ठा pci_slot *pci_slot, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;
	अचिन्हित दीर्घ ltest;
	u32 test;
	पूर्णांक retval = 0;

	ltest = simple_म_से_अदीर्घ(buf, शून्य, 10);
	test = (u32)(ltest & 0xffffffff);
	dbg("test = %d\n", test);

	अगर (!try_module_get(slot->owner)) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	अगर (slot->ops->hardware_test)
		retval = slot->ops->hardware_test(slot, test);
	module_put(slot->owner);

निकास:
	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण

अटल काष्ठा pci_slot_attribute hotplug_slot_attr_test = अणु
	.attr = अणु.name = "test", .mode = S_IFREG | S_IRUGO | S_IWUSRपूर्ण,
	.store = test_ग_लिखो_file
पूर्ण;

अटल bool has_घातer_file(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;

	अगर ((!slot) || (!slot->ops))
		वापस false;
	अगर ((slot->ops->enable_slot) ||
	    (slot->ops->disable_slot) ||
	    (slot->ops->get_घातer_status))
		वापस true;
	वापस false;
पूर्ण

अटल bool has_attention_file(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;

	अगर ((!slot) || (!slot->ops))
		वापस false;
	अगर ((slot->ops->set_attention_status) ||
	    (slot->ops->get_attention_status))
		वापस true;
	वापस false;
पूर्ण

अटल bool has_latch_file(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;

	अगर ((!slot) || (!slot->ops))
		वापस false;
	अगर (slot->ops->get_latch_status)
		वापस true;
	वापस false;
पूर्ण

अटल bool has_adapter_file(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;

	अगर ((!slot) || (!slot->ops))
		वापस false;
	अगर (slot->ops->get_adapter_status)
		वापस true;
	वापस false;
पूर्ण

अटल bool has_test_file(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;

	अगर ((!slot) || (!slot->ops))
		वापस false;
	अगर (slot->ops->hardware_test)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक fs_add_slot(काष्ठा pci_slot *pci_slot)
अणु
	पूर्णांक retval = 0;

	/* Create symbolic link to the hotplug driver module */
	pci_hp_create_module_link(pci_slot);

	अगर (has_घातer_file(pci_slot)) अणु
		retval = sysfs_create_file(&pci_slot->kobj,
					   &hotplug_slot_attr_घातer.attr);
		अगर (retval)
			जाओ निकास_घातer;
	पूर्ण

	अगर (has_attention_file(pci_slot)) अणु
		retval = sysfs_create_file(&pci_slot->kobj,
					   &hotplug_slot_attr_attention.attr);
		अगर (retval)
			जाओ निकास_attention;
	पूर्ण

	अगर (has_latch_file(pci_slot)) अणु
		retval = sysfs_create_file(&pci_slot->kobj,
					   &hotplug_slot_attr_latch.attr);
		अगर (retval)
			जाओ निकास_latch;
	पूर्ण

	अगर (has_adapter_file(pci_slot)) अणु
		retval = sysfs_create_file(&pci_slot->kobj,
					   &hotplug_slot_attr_presence.attr);
		अगर (retval)
			जाओ निकास_adapter;
	पूर्ण

	अगर (has_test_file(pci_slot)) अणु
		retval = sysfs_create_file(&pci_slot->kobj,
					   &hotplug_slot_attr_test.attr);
		अगर (retval)
			जाओ निकास_test;
	पूर्ण

	जाओ निकास;

निकास_test:
	अगर (has_adapter_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj,
				  &hotplug_slot_attr_presence.attr);
निकास_adapter:
	अगर (has_latch_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj, &hotplug_slot_attr_latch.attr);
निकास_latch:
	अगर (has_attention_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj,
				  &hotplug_slot_attr_attention.attr);
निकास_attention:
	अगर (has_घातer_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj, &hotplug_slot_attr_घातer.attr);
निकास_घातer:
	pci_hp_हटाओ_module_link(pci_slot);
निकास:
	वापस retval;
पूर्ण

अटल व्योम fs_हटाओ_slot(काष्ठा pci_slot *pci_slot)
अणु
	अगर (has_घातer_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj, &hotplug_slot_attr_घातer.attr);

	अगर (has_attention_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj,
				  &hotplug_slot_attr_attention.attr);

	अगर (has_latch_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj, &hotplug_slot_attr_latch.attr);

	अगर (has_adapter_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj,
				  &hotplug_slot_attr_presence.attr);

	अगर (has_test_file(pci_slot))
		sysfs_हटाओ_file(&pci_slot->kobj, &hotplug_slot_attr_test.attr);

	pci_hp_हटाओ_module_link(pci_slot);
पूर्ण

अटल काष्ठा hotplug_slot *get_slot_from_name(स्थिर अक्षर *name)
अणु
	काष्ठा hotplug_slot *slot;

	list_क्रम_each_entry(slot, &pci_hotplug_slot_list, slot_list) अणु
		अगर (म_भेद(hotplug_slot_name(slot), name) == 0)
			वापस slot;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * __pci_hp_रेजिस्टर - रेजिस्टर a hotplug_slot with the PCI hotplug subप्रणाली
 * @bus: bus this slot is on
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to रेजिस्टर
 * @devnr: device number
 * @name: name रेजिस्टरed with kobject core
 * @owner: caller module owner
 * @mod_name: caller module name
 *
 * Prepares a hotplug slot क्रम in-kernel use and immediately publishes it to
 * user space in one go.  Drivers may alternatively carry out the two steps
 * separately by invoking pci_hp_initialize() and pci_hp_add().
 *
 * Returns 0 अगर successful, anything अन्यथा क्रम an error.
 */
पूर्णांक __pci_hp_रेजिस्टर(काष्ठा hotplug_slot *slot, काष्ठा pci_bus *bus,
		      पूर्णांक devnr, स्थिर अक्षर *name,
		      काष्ठा module *owner, स्थिर अक्षर *mod_name)
अणु
	पूर्णांक result;

	result = __pci_hp_initialize(slot, bus, devnr, name, owner, mod_name);
	अगर (result)
		वापस result;

	result = pci_hp_add(slot);
	अगर (result)
		pci_hp_destroy(slot);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(__pci_hp_रेजिस्टर);

/**
 * __pci_hp_initialize - prepare hotplug slot क्रम in-kernel use
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to initialize
 * @bus: bus this slot is on
 * @devnr: slot number
 * @name: name रेजिस्टरed with kobject core
 * @owner: caller module owner
 * @mod_name: caller module name
 *
 * Allocate and fill in a PCI slot क्रम use by a hotplug driver.  Once this has
 * been called, the driver may invoke hotplug_slot_name() to get the slot's
 * unique name.  The driver must be prepared to handle a ->reset_slot callback
 * from this poपूर्णांक on.
 *
 * Returns 0 on success or a negative पूर्णांक on error.
 */
पूर्णांक __pci_hp_initialize(काष्ठा hotplug_slot *slot, काष्ठा pci_bus *bus,
			पूर्णांक devnr, स्थिर अक्षर *name, काष्ठा module *owner,
			स्थिर अक्षर *mod_name)
अणु
	काष्ठा pci_slot *pci_slot;

	अगर (slot == शून्य)
		वापस -ENODEV;
	अगर (slot->ops == शून्य)
		वापस -EINVAL;

	slot->owner = owner;
	slot->mod_name = mod_name;

	/*
	 * No problems अगर we call this पूर्णांकerface from both ACPI_PCI_SLOT
	 * driver and call it here again. If we've alपढ़ोy created the
	 * pci_slot, the पूर्णांकerface will simply bump the refcount.
	 */
	pci_slot = pci_create_slot(bus, devnr, name, slot);
	अगर (IS_ERR(pci_slot))
		वापस PTR_ERR(pci_slot);

	slot->pci_slot = pci_slot;
	pci_slot->hotplug = slot;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__pci_hp_initialize);

/**
 * pci_hp_add - publish hotplug slot to user space
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to publish
 *
 * Make a hotplug slot's sysfs पूर्णांकerface available and inक्रमm user space of its
 * addition by sending a uevent.  The hotplug driver must be prepared to handle
 * all &काष्ठा hotplug_slot_ops callbacks from this poपूर्णांक on.
 *
 * Returns 0 on success or a negative पूर्णांक on error.
 */
पूर्णांक pci_hp_add(काष्ठा hotplug_slot *slot)
अणु
	काष्ठा pci_slot *pci_slot = slot->pci_slot;
	पूर्णांक result;

	result = fs_add_slot(pci_slot);
	अगर (result)
		वापस result;

	kobject_uevent(&pci_slot->kobj, KOBJ_ADD);
	mutex_lock(&pci_hp_mutex);
	list_add(&slot->slot_list, &pci_hotplug_slot_list);
	mutex_unlock(&pci_hp_mutex);
	dbg("Added slot %s to the list\n", hotplug_slot_name(slot));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_add);

/**
 * pci_hp_deरेजिस्टर - deरेजिस्टर a hotplug_slot with the PCI hotplug subप्रणाली
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to deरेजिस्टर
 *
 * The @slot must have been रेजिस्टरed with the pci hotplug subप्रणाली
 * previously with a call to pci_hp_रेजिस्टर().
 *
 * Returns 0 अगर successful, anything अन्यथा क्रम an error.
 */
व्योम pci_hp_deरेजिस्टर(काष्ठा hotplug_slot *slot)
अणु
	pci_hp_del(slot);
	pci_hp_destroy(slot);
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_deरेजिस्टर);

/**
 * pci_hp_del - unpublish hotplug slot from user space
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to unpublish
 *
 * Remove a hotplug slot's sysfs पूर्णांकerface.
 *
 * Returns 0 on success or a negative पूर्णांक on error.
 */
व्योम pci_hp_del(काष्ठा hotplug_slot *slot)
अणु
	काष्ठा hotplug_slot *temp;

	अगर (WARN_ON(!slot))
		वापस;

	mutex_lock(&pci_hp_mutex);
	temp = get_slot_from_name(hotplug_slot_name(slot));
	अगर (WARN_ON(temp != slot)) अणु
		mutex_unlock(&pci_hp_mutex);
		वापस;
	पूर्ण

	list_del(&slot->slot_list);
	mutex_unlock(&pci_hp_mutex);
	dbg("Removed slot %s from the list\n", hotplug_slot_name(slot));
	fs_हटाओ_slot(slot->pci_slot);
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_del);

/**
 * pci_hp_destroy - हटाओ hotplug slot from in-kernel use
 * @slot: poपूर्णांकer to the &काष्ठा hotplug_slot to destroy
 *
 * Destroy a PCI slot used by a hotplug driver.  Once this has been called,
 * the driver may no दीर्घer invoke hotplug_slot_name() to get the slot's
 * unique name.  The driver no दीर्घer needs to handle a ->reset_slot callback
 * from this poपूर्णांक on.
 *
 * Returns 0 on success or a negative पूर्णांक on error.
 */
व्योम pci_hp_destroy(काष्ठा hotplug_slot *slot)
अणु
	काष्ठा pci_slot *pci_slot = slot->pci_slot;

	slot->pci_slot = शून्य;
	pci_slot->hotplug = शून्य;
	pci_destroy_slot(pci_slot);
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_destroy);

अटल पूर्णांक __init pci_hotplug_init(व्योम)
अणु
	पूर्णांक result;

	result = cpci_hotplug_init(debug);
	अगर (result) अणु
		err("cpci_hotplug_init with error %d\n", result);
		वापस result;
	पूर्ण

	वापस result;
पूर्ण
device_initcall(pci_hotplug_init);

/*
 * not really modular, but the easiest way to keep compat with existing
 * bootargs behaviour is to जारी using module_param here.
 */
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debugging mode enabled or not");
