<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2006 Matthew Wilcox <matthew@wil.cx>
 * Copyright (C) 2006-2009 Hewlett-Packard Development Company, L.P.
 *	Alex Chiang <achiang@hp.com>
 */

#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/err.h>
#समावेश "pci.h"

काष्ठा kset *pci_slots_kset;
EXPORT_SYMBOL_GPL(pci_slots_kset);

अटल sमाप_प्रकार pci_slot_attr_show(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_slot *slot = to_pci_slot(kobj);
	काष्ठा pci_slot_attribute *attribute = to_pci_slot_attr(attr);
	वापस attribute->show ? attribute->show(slot, buf) : -EIO;
पूर्ण

अटल sमाप_प्रकार pci_slot_attr_store(काष्ठा kobject *kobj,
			काष्ठा attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pci_slot *slot = to_pci_slot(kobj);
	काष्ठा pci_slot_attribute *attribute = to_pci_slot_attr(attr);
	वापस attribute->store ? attribute->store(slot, buf, len) : -EIO;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops pci_slot_sysfs_ops = अणु
	.show = pci_slot_attr_show,
	.store = pci_slot_attr_store,
पूर्ण;

अटल sमाप_प्रकार address_पढ़ो_file(काष्ठा pci_slot *slot, अक्षर *buf)
अणु
	अगर (slot->number == 0xff)
		वापस प्र_लिखो(buf, "%04x:%02x\n",
				pci_करोमुख्य_nr(slot->bus),
				slot->bus->number);
	अन्यथा
		वापस प्र_लिखो(buf, "%04x:%02x:%02x\n",
				pci_करोमुख्य_nr(slot->bus),
				slot->bus->number,
				slot->number);
पूर्ण

अटल sमाप_प्रकार bus_speed_पढ़ो(क्रमागत pci_bus_speed speed, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", pci_speed_string(speed));
पूर्ण

अटल sमाप_प्रकार max_speed_पढ़ो_file(काष्ठा pci_slot *slot, अक्षर *buf)
अणु
	वापस bus_speed_पढ़ो(slot->bus->max_bus_speed, buf);
पूर्ण

अटल sमाप_प्रकार cur_speed_पढ़ो_file(काष्ठा pci_slot *slot, अक्षर *buf)
अणु
	वापस bus_speed_पढ़ो(slot->bus->cur_bus_speed, buf);
पूर्ण

अटल व्योम pci_slot_release(काष्ठा kobject *kobj)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_slot *slot = to_pci_slot(kobj);

	dev_dbg(&slot->bus->dev, "dev %02x, released physical slot %s\n",
		slot->number, pci_slot_name(slot));

	करोwn_पढ़ो(&pci_bus_sem);
	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list)
		अगर (PCI_SLOT(dev->devfn) == slot->number)
			dev->slot = शून्य;
	up_पढ़ो(&pci_bus_sem);

	list_del(&slot->list);

	kमुक्त(slot);
पूर्ण

अटल काष्ठा pci_slot_attribute pci_slot_attr_address =
	__ATTR(address, S_IRUGO, address_पढ़ो_file, शून्य);
अटल काष्ठा pci_slot_attribute pci_slot_attr_max_speed =
	__ATTR(max_bus_speed, S_IRUGO, max_speed_पढ़ो_file, शून्य);
अटल काष्ठा pci_slot_attribute pci_slot_attr_cur_speed =
	__ATTR(cur_bus_speed, S_IRUGO, cur_speed_पढ़ो_file, शून्य);

अटल काष्ठा attribute *pci_slot_शेष_attrs[] = अणु
	&pci_slot_attr_address.attr,
	&pci_slot_attr_max_speed.attr,
	&pci_slot_attr_cur_speed.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type pci_slot_ktype = अणु
	.sysfs_ops = &pci_slot_sysfs_ops,
	.release = &pci_slot_release,
	.शेष_attrs = pci_slot_शेष_attrs,
पूर्ण;

अटल अक्षर *make_slot_name(स्थिर अक्षर *name)
अणु
	अक्षर *new_name;
	पूर्णांक len, max, dup;

	new_name = kstrdup(name, GFP_KERNEL);
	अगर (!new_name)
		वापस शून्य;

	/*
	 * Make sure we hit the पुनः_स्मृति हाल the first समय through the
	 * loop.  'len' will be म_माप(name) + 3 at that poपूर्णांक which is
	 * enough space क्रम "name-X" and the trailing NUL.
	 */
	len = म_माप(name) + 2;
	max = 1;
	dup = 1;

	क्रम (;;) अणु
		काष्ठा kobject *dup_slot;
		dup_slot = kset_find_obj(pci_slots_kset, new_name);
		अगर (!dup_slot)
			अवरोध;
		kobject_put(dup_slot);
		अगर (dup == max) अणु
			len++;
			max *= 10;
			kमुक्त(new_name);
			new_name = kदो_स्मृति(len, GFP_KERNEL);
			अगर (!new_name)
				अवरोध;
		पूर्ण
		प्र_लिखो(new_name, "%s-%d", name, dup++);
	पूर्ण

	वापस new_name;
पूर्ण

अटल पूर्णांक नाम_slot(काष्ठा pci_slot *slot, स्थिर अक्षर *name)
अणु
	पूर्णांक result = 0;
	अक्षर *slot_name;

	अगर (म_भेद(pci_slot_name(slot), name) == 0)
		वापस result;

	slot_name = make_slot_name(name);
	अगर (!slot_name)
		वापस -ENOMEM;

	result = kobject_नाम(&slot->kobj, slot_name);
	kमुक्त(slot_name);

	वापस result;
पूर्ण

व्योम pci_dev_assign_slot(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_slot *slot;

	mutex_lock(&pci_slot_mutex);
	list_क्रम_each_entry(slot, &dev->bus->slots, list)
		अगर (PCI_SLOT(dev->devfn) == slot->number)
			dev->slot = slot;
	mutex_unlock(&pci_slot_mutex);
पूर्ण

अटल काष्ठा pci_slot *get_slot(काष्ठा pci_bus *parent, पूर्णांक slot_nr)
अणु
	काष्ठा pci_slot *slot;

	/* We alपढ़ोy hold pci_slot_mutex */
	list_क्रम_each_entry(slot, &parent->slots, list)
		अगर (slot->number == slot_nr) अणु
			kobject_get(&slot->kobj);
			वापस slot;
		पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pci_create_slot - create or increment refcount क्रम physical PCI slot
 * @parent: काष्ठा pci_bus of parent bridge
 * @slot_nr: PCI_SLOT(pci_dev->devfn) or -1 क्रम placeholder
 * @name: user visible string presented in /sys/bus/pci/slots/<name>
 * @hotplug: set अगर caller is hotplug driver, शून्य otherwise
 *
 * PCI slots have first class attributes such as address, speed, width,
 * and a &काष्ठा pci_slot is used to manage them. This पूर्णांकerface will
 * either वापस a new &काष्ठा pci_slot to the caller, or अगर the pci_slot
 * alपढ़ोy exists, its refcount will be incremented.
 *
 * Slots are uniquely identअगरied by a @pci_bus, @slot_nr tuple.
 *
 * There are known platक्रमms with broken firmware that assign the same
 * name to multiple slots. Workaround these broken platक्रमms by renaming
 * the slots on behalf of the caller. If firmware assigns name N to
 * multiple slots:
 *
 * The first slot is asचिन्हित N
 * The second slot is asचिन्हित N-1
 * The third slot is asचिन्हित N-2
 * etc.
 *
 * Placeholder slots:
 * In most हालs, @pci_bus, @slot_nr will be sufficient to uniquely identअगरy
 * a slot. There is one notable exception - pSeries (rpaphp), where the
 * @slot_nr cannot be determined until a device is actually inserted पूर्णांकo
 * the slot. In this scenario, the caller may pass -1 क्रम @slot_nr.
 *
 * The following semantics are imposed when the caller passes @slot_nr ==
 * -1. First, we no दीर्घer check क्रम an existing %काष्ठा pci_slot, as there
 * may be many slots with @slot_nr of -1.  The other change in semantics is
 * user-visible, which is the 'address' parameter presented in sysfs will
 * consist solely of a dddd:bb tuple, where dddd is the PCI करोमुख्य of the
 * %काष्ठा pci_bus and bb is the bus number. In other words, the devfn of
 * the 'placeholder' slot will not be displayed.
 */
काष्ठा pci_slot *pci_create_slot(काष्ठा pci_bus *parent, पूर्णांक slot_nr,
				 स्थिर अक्षर *name,
				 काष्ठा hotplug_slot *hotplug)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_slot *slot;
	पूर्णांक err = 0;
	अक्षर *slot_name = शून्य;

	mutex_lock(&pci_slot_mutex);

	अगर (slot_nr == -1)
		जाओ placeholder;

	/*
	 * Hotplug drivers are allowed to नाम an existing slot,
	 * but only अगर not alपढ़ोy claimed.
	 */
	slot = get_slot(parent, slot_nr);
	अगर (slot) अणु
		अगर (hotplug) अणु
			अगर ((err = slot->hotplug ? -EBUSY : 0)
			     || (err = नाम_slot(slot, name))) अणु
				kobject_put(&slot->kobj);
				slot = शून्य;
				जाओ err;
			पूर्ण
		पूर्ण
		जाओ out;
	पूर्ण

placeholder:
	slot = kzalloc(माप(*slot), GFP_KERNEL);
	अगर (!slot) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	slot->bus = parent;
	slot->number = slot_nr;

	slot->kobj.kset = pci_slots_kset;

	slot_name = make_slot_name(name);
	अगर (!slot_name) अणु
		err = -ENOMEM;
		kमुक्त(slot);
		जाओ err;
	पूर्ण

	INIT_LIST_HEAD(&slot->list);
	list_add(&slot->list, &parent->slots);

	err = kobject_init_and_add(&slot->kobj, &pci_slot_ktype, शून्य,
				   "%s", slot_name);
	अगर (err) अणु
		kobject_put(&slot->kobj);
		जाओ err;
	पूर्ण

	करोwn_पढ़ो(&pci_bus_sem);
	list_क्रम_each_entry(dev, &parent->devices, bus_list)
		अगर (PCI_SLOT(dev->devfn) == slot_nr)
			dev->slot = slot;
	up_पढ़ो(&pci_bus_sem);

	dev_dbg(&parent->dev, "dev %02x, created physical slot %s\n",
		slot_nr, pci_slot_name(slot));

out:
	kमुक्त(slot_name);
	mutex_unlock(&pci_slot_mutex);
	वापस slot;
err:
	slot = ERR_PTR(err);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(pci_create_slot);

/**
 * pci_destroy_slot - decrement refcount क्रम physical PCI slot
 * @slot: काष्ठा pci_slot to decrement
 *
 * %काष्ठा pci_slot is refcounted, so destroying them is really easy; we
 * just call kobject_put on its kobj and let our release methods करो the
 * rest.
 */
व्योम pci_destroy_slot(काष्ठा pci_slot *slot)
अणु
	dev_dbg(&slot->bus->dev, "dev %02x, dec refcount to %d\n",
		slot->number, kref_पढ़ो(&slot->kobj.kref) - 1);

	mutex_lock(&pci_slot_mutex);
	kobject_put(&slot->kobj);
	mutex_unlock(&pci_slot_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pci_destroy_slot);

#अगर defined(CONFIG_HOTPLUG_PCI) || defined(CONFIG_HOTPLUG_PCI_MODULE)
#समावेश <linux/pci_hotplug.h>
/**
 * pci_hp_create_module_link - create symbolic link to hotplug driver module
 * @pci_slot: काष्ठा pci_slot
 *
 * Helper function क्रम pci_hotplug_core.c to create symbolic link to
 * the hotplug driver module.
 */
व्योम pci_hp_create_module_link(काष्ठा pci_slot *pci_slot)
अणु
	काष्ठा hotplug_slot *slot = pci_slot->hotplug;
	काष्ठा kobject *kobj = शून्य;
	पूर्णांक ret;

	अगर (!slot || !slot->ops)
		वापस;
	kobj = kset_find_obj(module_kset, slot->mod_name);
	अगर (!kobj)
		वापस;
	ret = sysfs_create_link(&pci_slot->kobj, kobj, "module");
	अगर (ret)
		dev_err(&pci_slot->bus->dev, "Error creating sysfs link (%d)\n",
			ret);
	kobject_put(kobj);
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_create_module_link);

/**
 * pci_hp_हटाओ_module_link - हटाओ symbolic link to the hotplug driver
 * 	module.
 * @pci_slot: काष्ठा pci_slot
 *
 * Helper function क्रम pci_hotplug_core.c to हटाओ symbolic link to
 * the hotplug driver module.
 */
व्योम pci_hp_हटाओ_module_link(काष्ठा pci_slot *pci_slot)
अणु
	sysfs_हटाओ_link(&pci_slot->kobj, "module");
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_हटाओ_module_link);
#पूर्ण_अगर

अटल पूर्णांक pci_slot_init(व्योम)
अणु
	काष्ठा kset *pci_bus_kset;

	pci_bus_kset = bus_get_kset(&pci_bus_type);
	pci_slots_kset = kset_create_and_add("slots", शून्य,
						&pci_bus_kset->kobj);
	अगर (!pci_slots_kset) अणु
		pr_err("PCI: Slot initialization failure\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

subsys_initcall(pci_slot_init);
