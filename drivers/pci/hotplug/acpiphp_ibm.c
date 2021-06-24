<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ACPI PCI Hot Plug IBM Extension
 *
 * Copyright (C) 2004 Vernon Mauery <vernux@us.ibm.com>
 * Copyright (C) 2004 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <vernux@us.ibm.com>
 *
 */

#घोषणा pr_fmt(fmt) "acpiphp_ibm: " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश "acpiphp.h"
#समावेश "../pci.h"

#घोषणा DRIVER_VERSION	"1.0.1"
#घोषणा DRIVER_AUTHOR	"Irene Zubarev <zubarev@us.ibm.com>, Vernon Mauery <vernux@us.ibm.com>"
#घोषणा DRIVER_DESC	"ACPI Hot Plug PCI Controller Driver IBM extension"


MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

#घोषणा FOUND_APCI 0x61504349
/* these are the names क्रम the IBM ACPI pseuकरो-device */
#घोषणा IBM_HARDWARE_ID1 "IBM37D0"
#घोषणा IBM_HARDWARE_ID2 "IBM37D4"

#घोषणा hpslot_to_sun(A) (to_slot(A)->sun)

/* जोड़ apci_descriptor - allows access to the
 * various device descriptors that are embedded in the
 * aPCI table
 */
जोड़ apci_descriptor अणु
	काष्ठा अणु
		अक्षर sig[4];
		u8   len;
	पूर्ण header;
	काष्ठा अणु
		u8  type;
		u8  len;
		u16 slot_id;
		u8  bus_id;
		u8  dev_num;
		u8  slot_num;
		u8  slot_attr[2];
		u8  attn;
		u8  status[2];
		u8  sun;
		u8  res[3];
	पूर्ण slot;
	काष्ठा अणु
		u8 type;
		u8 len;
	पूर्ण generic;
पूर्ण;

/* काष्ठा notअगरication - keeps info about the device
 * that cause the ACPI notअगरication event
 */
काष्ठा notअगरication अणु
	काष्ठा acpi_device *device;
	u8                  event;
पूर्ण;

अटल पूर्णांक ibm_set_attention_status(काष्ठा hotplug_slot *slot, u8 status);
अटल पूर्णांक ibm_get_attention_status(काष्ठा hotplug_slot *slot, u8 *status);
अटल व्योम ibm_handle_events(acpi_handle handle, u32 event, व्योम *context);
अटल पूर्णांक ibm_get_table_from_acpi(अक्षर **bufp);
अटल sमाप_प्रकार ibm_पढ़ो_apci_table(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr,
				   अक्षर *buffer, loff_t pos, माप_प्रकार size);
अटल acpi_status __init ibm_find_acpi_device(acpi_handle handle,
		u32 lvl, व्योम *context, व्योम **rv);
अटल पूर्णांक __init ibm_acpiphp_init(व्योम);
अटल व्योम __निकास ibm_acpiphp_निकास(व्योम);

अटल acpi_handle ibm_acpi_handle;
अटल काष्ठा notअगरication ibm_note;
अटल काष्ठा bin_attribute ibm_apci_table_attr __ro_after_init = अणु
	    .attr = अणु
		    .name = "apci_table",
		    .mode = S_IRUGO,
	    पूर्ण,
	    .पढ़ो = ibm_पढ़ो_apci_table,
	    .ग_लिखो = शून्य,
पूर्ण;
अटल काष्ठा acpiphp_attention_info ibm_attention_info =
अणु
	.set_attn = ibm_set_attention_status,
	.get_attn = ibm_get_attention_status,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * ibm_slot_from_id - workaround क्रम bad ibm hardware
 * @id: the slot number that linux refers to the slot by
 *
 * Description: This method वापसs the aCPI slot descriptor
 * corresponding to the Linux slot number.  This descriptor
 * has info about the aPCI slot id and attention status.
 * This descriptor must be मुक्तd using kमुक्त when करोne.
 */
अटल जोड़ apci_descriptor *ibm_slot_from_id(पूर्णांक id)
अणु
	पूर्णांक ind = 0, size;
	जोड़ apci_descriptor *ret = शून्य, *des;
	अक्षर *table;

	size = ibm_get_table_from_acpi(&table);
	अगर (size < 0)
		वापस शून्य;
	des = (जोड़ apci_descriptor *)table;
	अगर (स_भेद(des->header.sig, "aPCI", 4) != 0)
		जाओ ibm_slot_करोne;

	des = (जोड़ apci_descriptor *)&table[ind += des->header.len];
	जबतक (ind < size && (des->generic.type != 0x82 ||
			des->slot.slot_num != id)) अणु
		des = (जोड़ apci_descriptor *)&table[ind += des->generic.len];
	पूर्ण

	अगर (ind < size && des->slot.slot_num == id)
		ret = des;

ibm_slot_करोne:
	अगर (ret) अणु
		ret = kदो_स्मृति(माप(जोड़ apci_descriptor), GFP_KERNEL);
		अगर (ret)
			स_नकल(ret, des, माप(जोड़ apci_descriptor));
	पूर्ण
	kमुक्त(table);
	वापस ret;
पूर्ण

/**
 * ibm_set_attention_status - callback method to set the attention LED
 * @slot: the hotplug_slot to work with
 * @status: what to set the LED to (0 or 1)
 *
 * Description: This method is रेजिस्टरed with the acpiphp module as a
 * callback to करो the device specअगरic task of setting the LED status.
 */
अटल पूर्णांक ibm_set_attention_status(काष्ठा hotplug_slot *slot, u8 status)
अणु
	जोड़ acpi_object args[2];
	काष्ठा acpi_object_list params = अणु .poपूर्णांकer = args, .count = 2 पूर्ण;
	acpi_status stat;
	अचिन्हित दीर्घ दीर्घ rc;
	जोड़ apci_descriptor *ibm_slot;
	पूर्णांक id = hpslot_to_sun(slot);

	ibm_slot = ibm_slot_from_id(id);
	अगर (!ibm_slot) अणु
		pr_err("APLS null ACPI descriptor for slot %d\n", id);
		वापस -ENODEV;
	पूर्ण

	pr_debug("%s: set slot %d (%d) attention status to %d\n", __func__,
			ibm_slot->slot.slot_num, ibm_slot->slot.slot_id,
			(status ? 1 : 0));

	args[0].type = ACPI_TYPE_INTEGER;
	args[0].पूर्णांकeger.value = ibm_slot->slot.slot_id;
	args[1].type = ACPI_TYPE_INTEGER;
	args[1].पूर्णांकeger.value = (status) ? 1 : 0;

	kमुक्त(ibm_slot);

	stat = acpi_evaluate_पूर्णांकeger(ibm_acpi_handle, "APLS", &params, &rc);
	अगर (ACPI_FAILURE(stat)) अणु
		pr_err("APLS evaluation failed:  0x%08x\n", stat);
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (!rc) अणु
		pr_err("APLS method failed:  0x%08llx\n", rc);
		वापस -दुस्फल;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ibm_get_attention_status - callback method to get attention LED status
 * @slot: the hotplug_slot to work with
 * @status: वापसs what the LED is set to (0 or 1)
 *
 * Description: This method is रेजिस्टरed with the acpiphp module as a
 * callback to करो the device specअगरic task of getting the LED status.
 *
 * Because there is no direct method of getting the LED status directly
 * from an ACPI call, we पढ़ो the aPCI table and parse out our
 * slot descriptor to पढ़ो the status from that.
 */
अटल पूर्णांक ibm_get_attention_status(काष्ठा hotplug_slot *slot, u8 *status)
अणु
	जोड़ apci_descriptor *ibm_slot;
	पूर्णांक id = hpslot_to_sun(slot);

	ibm_slot = ibm_slot_from_id(id);
	अगर (!ibm_slot) अणु
		pr_err("APLS null ACPI descriptor for slot %d\n", id);
		वापस -ENODEV;
	पूर्ण

	अगर (ibm_slot->slot.attn & 0xa0 || ibm_slot->slot.status[1] & 0x08)
		*status = 1;
	अन्यथा
		*status = 0;

	pr_debug("%s: get slot %d (%d) attention status is %d\n", __func__,
			ibm_slot->slot.slot_num, ibm_slot->slot.slot_id,
			*status);

	kमुक्त(ibm_slot);
	वापस 0;
पूर्ण

/**
 * ibm_handle_events - listens क्रम ACPI events क्रम the IBM37D0 device
 * @handle: an ACPI handle to the device that caused the event
 * @event: the event info (device specअगरic)
 * @context: passed context (our notअगरication काष्ठा)
 *
 * Description: This method is रेजिस्टरed as a callback with the ACPI
 * subप्रणाली it is called when this device has an event to notअगरy the OS of.
 *
 * The events actually come from the device as two events that get
 * synthesized पूर्णांकo one event with data by this function.  The event
 * ID comes first and then the slot number that caused it.  We report
 * this as one event to the OS.
 *
 * From section 5.6.2.2 of the ACPI 2.0 spec, I understand that the OSPM will
 * only re-enable the पूर्णांकerrupt that causes this event AFTER this method
 * has वापसed, thereby enक्रमcing serial access क्रम the notअगरication काष्ठा.
 */
अटल व्योम ibm_handle_events(acpi_handle handle, u32 event, व्योम *context)
अणु
	u8 detail = event & 0x0f;
	u8 subevent = event & 0xf0;
	काष्ठा notअगरication *note = context;

	pr_debug("%s: Received notification %02x\n", __func__, event);

	अगर (subevent == 0x80) अणु
		pr_debug("%s: generating bus event\n", __func__);
		acpi_bus_generate_netlink_event(note->device->pnp.device_class,
						  dev_name(&note->device->dev),
						  note->event, detail);
	पूर्ण अन्यथा
		note->event = event;
पूर्ण

/**
 * ibm_get_table_from_acpi - पढ़ोs the APLS buffer from ACPI
 * @bufp: address to poपूर्णांकer to allocate क्रम the table
 *
 * Description: This method पढ़ोs the APLS buffer in from ACPI and
 * stores the "stripped" table पूर्णांकo a single buffer
 * it allocates and passes the address back in bufp.
 *
 * If शून्य is passed in as buffer, this method only calculates
 * the size of the table and वापसs that without filling
 * in the buffer.
 *
 * Returns < 0 on error or the size of the table on success.
 */
अटल पूर्णांक ibm_get_table_from_acpi(अक्षर **bufp)
अणु
	जोड़ acpi_object *package;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;
	अक्षर *lbuf = शून्य;
	पूर्णांक i, size = -EIO;

	status = acpi_evaluate_object(ibm_acpi_handle, "APCI", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("%s:  APCI evaluation failed\n", __func__);
		वापस -ENODEV;
	पूर्ण

	package = (जोड़ acpi_object *) buffer.poपूर्णांकer;
	अगर (!(package) ||
			(package->type != ACPI_TYPE_PACKAGE) ||
			!(package->package.elements)) अणु
		pr_err("%s:  Invalid APCI object\n", __func__);
		जाओ पढ़ो_table_करोne;
	पूर्ण

	क्रम (size = 0, i = 0; i < package->package.count; i++) अणु
		अगर (package->package.elements[i].type != ACPI_TYPE_BUFFER) अणु
			pr_err("%s:  Invalid APCI element %d\n", __func__, i);
			जाओ पढ़ो_table_करोne;
		पूर्ण
		size += package->package.elements[i].buffer.length;
	पूर्ण

	अगर (bufp == शून्य)
		जाओ पढ़ो_table_करोne;

	lbuf = kzalloc(size, GFP_KERNEL);
	pr_debug("%s: element count: %i, ASL table size: %i, &table = 0x%p\n",
			__func__, package->package.count, size, lbuf);

	अगर (lbuf) अणु
		*bufp = lbuf;
	पूर्ण अन्यथा अणु
		size = -ENOMEM;
		जाओ पढ़ो_table_करोne;
	पूर्ण

	size = 0;
	क्रम (i = 0; i < package->package.count; i++) अणु
		स_नकल(&lbuf[size],
				package->package.elements[i].buffer.poपूर्णांकer,
				package->package.elements[i].buffer.length);
		size += package->package.elements[i].buffer.length;
	पूर्ण

पढ़ो_table_करोne:
	kमुक्त(buffer.poपूर्णांकer);
	वापस size;
पूर्ण

/**
 * ibm_पढ़ो_apci_table - callback क्रम the sysfs apci_table file
 * @filp: the खोलो sysfs file
 * @kobj: the kobject this binary attribute is a part of
 * @bin_attr: काष्ठा bin_attribute क्रम this file
 * @buffer: the kernel space buffer to fill
 * @pos: the offset पूर्णांकo the file
 * @size: the number of bytes requested
 *
 * Description: Gets रेजिस्टरed with sysfs as the पढ़ोer callback
 * to be executed when /sys/bus/pci/slots/apci_table माला_लो पढ़ो.
 *
 * Since we करोn't get notअगरied on खोलो and बंद क्रम this file,
 * things get really tricky here...
 * our solution is to only allow पढ़ोing the table in all at once.
 */
अटल sमाप_प्रकार ibm_पढ़ो_apci_table(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr,
				   अक्षर *buffer, loff_t pos, माप_प्रकार size)
अणु
	पूर्णांक bytes_पढ़ो = -EINVAL;
	अक्षर *table = शून्य;

	pr_debug("%s: pos = %d, size = %zd\n", __func__, (पूर्णांक)pos, size);

	अगर (pos == 0) अणु
		bytes_पढ़ो = ibm_get_table_from_acpi(&table);
		अगर (bytes_पढ़ो > 0 && bytes_पढ़ो <= size)
			स_नकल(buffer, table, bytes_पढ़ो);
		kमुक्त(table);
	पूर्ण
	वापस bytes_पढ़ो;
पूर्ण

/**
 * ibm_find_acpi_device - callback to find our ACPI device
 * @handle: the ACPI handle of the device we are inspecting
 * @lvl: depth पूर्णांकo the namespace tree
 * @context: a poपूर्णांकer to our handle to fill when we find the device
 * @rv: a वापस value to fill अगर desired
 *
 * Description: Used as a callback when calling acpi_walk_namespace
 * to find our device.  When this method वापसs non-zero
 * acpi_walk_namespace quits its search and वापसs our value.
 */
अटल acpi_status __init ibm_find_acpi_device(acpi_handle handle,
		u32 lvl, व्योम *context, व्योम **rv)
अणु
	acpi_handle *phandle = (acpi_handle *)context;
	अचिन्हित दीर्घ दीर्घ current_status = 0;
	acpi_status status;
	काष्ठा acpi_device_info *info;
	पूर्णांक retval = 0;

	status = acpi_get_object_info(handle, &info);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("%s:  Failed to get device information status=0x%x\n",
			__func__, status);
		वापस retval;
	पूर्ण

	acpi_bus_get_status_handle(handle, &current_status);

	अगर (current_status && (info->valid & ACPI_VALID_HID) &&
			(!म_भेद(info->hardware_id.string, IBM_HARDWARE_ID1) ||
			 !म_भेद(info->hardware_id.string, IBM_HARDWARE_ID2))) अणु
		pr_debug("found hardware: %s, handle: %p\n",
			info->hardware_id.string, handle);
		*phandle = handle;
		/* वापसing non-zero causes the search to stop
		 * and वापसs this value to the caller of
		 * acpi_walk_namespace, but it also causes some warnings
		 * in the acpi debug code to prपूर्णांक...
		 */
		retval = FOUND_APCI;
	पूर्ण
	kमुक्त(info);
	वापस retval;
पूर्ण

अटल पूर्णांक __init ibm_acpiphp_init(व्योम)
अणु
	पूर्णांक retval = 0;
	acpi_status status;
	काष्ठा acpi_device *device;
	काष्ठा kobject *sysdir = &pci_slots_kset->kobj;

	pr_debug("%s\n", __func__);

	अगर (acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
			ACPI_UINT32_MAX, ibm_find_acpi_device, शून्य,
			&ibm_acpi_handle, शून्य) != FOUND_APCI) अणु
		pr_err("%s: acpi_walk_namespace failed\n", __func__);
		retval = -ENODEV;
		जाओ init_वापस;
	पूर्ण
	pr_debug("%s: found IBM aPCI device\n", __func__);
	अगर (acpi_bus_get_device(ibm_acpi_handle, &device)) अणु
		pr_err("%s: acpi_bus_get_device failed\n", __func__);
		retval = -ENODEV;
		जाओ init_वापस;
	पूर्ण
	अगर (acpiphp_रेजिस्टर_attention(&ibm_attention_info)) अणु
		retval = -ENODEV;
		जाओ init_वापस;
	पूर्ण

	ibm_note.device = device;
	status = acpi_install_notअगरy_handler(ibm_acpi_handle,
			ACPI_DEVICE_NOTIFY, ibm_handle_events,
			&ibm_note);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("%s: Failed to register notification handler\n",
				__func__);
		retval = -EBUSY;
		जाओ init_cleanup;
	पूर्ण

	ibm_apci_table_attr.size = ibm_get_table_from_acpi(शून्य);
	retval = sysfs_create_bin_file(sysdir, &ibm_apci_table_attr);

	वापस retval;

init_cleanup:
	acpiphp_unरेजिस्टर_attention(&ibm_attention_info);
init_वापस:
	वापस retval;
पूर्ण

अटल व्योम __निकास ibm_acpiphp_निकास(व्योम)
अणु
	acpi_status status;
	काष्ठा kobject *sysdir = &pci_slots_kset->kobj;

	pr_debug("%s\n", __func__);

	अगर (acpiphp_unरेजिस्टर_attention(&ibm_attention_info))
		pr_err("%s: attention info deregistration failed", __func__);

	status = acpi_हटाओ_notअगरy_handler(
			   ibm_acpi_handle,
			   ACPI_DEVICE_NOTIFY,
			   ibm_handle_events);
	अगर (ACPI_FAILURE(status))
		pr_err("%s: Notification handler removal failed\n", __func__);
	/* हटाओ the /sys entries */
	sysfs_हटाओ_bin_file(sysdir, &ibm_apci_table_attr);
पूर्ण

module_init(ibm_acpiphp_init);
module_निकास(ibm_acpiphp_निकास);
