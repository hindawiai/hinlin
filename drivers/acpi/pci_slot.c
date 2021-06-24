<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  pci_slot.c - ACPI PCI Slot Driver
 *
 *  The code here is heavily leveraged from the acpiphp module.
 *  Thanks to Matthew Wilcox <matthew@wil.cx> क्रम much guidance.
 *  Thanks to Kenji Kaneshige <kaneshige.kenji@jp.fujitsu.com> क्रम code
 *  review and fixes.
 *
 *  Copyright (C) 2007-2008 Hewlett-Packard Development Company, L.P.
 *  	Alex Chiang <achiang@hp.com>
 *
 *  Copyright (C) 2013 Huawei Tech. Co., Ltd.
 *	Jiang Liu <jiang.liu@huawei.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci-acpi.h>

अटल पूर्णांक check_sta_beक्रमe_sun;

#घोषणा SLOT_NAME_SIZE 21		/* Inspired by #घोषणा in acpiphp.h */

काष्ठा acpi_pci_slot अणु
	काष्ठा pci_slot *pci_slot;	/* corresponding pci_slot */
	काष्ठा list_head list;		/* node in the list of slots */
पूर्ण;

अटल LIST_HEAD(slot_list);
अटल DEFINE_MUTEX(slot_list_lock);

अटल पूर्णांक
check_slot(acpi_handle handle, अचिन्हित दीर्घ दीर्घ *sun)
अणु
	पूर्णांक device = -1;
	अचिन्हित दीर्घ दीर्घ adr, sta;
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
	pr_debug("Checking slot on path: %s\n", (अक्षर *)buffer.poपूर्णांकer);

	अगर (check_sta_beक्रमe_sun) अणु
		/* If SxFy करोesn't have _STA, we just assume it's there */
		status = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, &sta);
		अगर (ACPI_SUCCESS(status) && !(sta & ACPI_STA_DEVICE_PRESENT))
			जाओ out;
	पूर्ण

	status = acpi_evaluate_पूर्णांकeger(handle, "_ADR", शून्य, &adr);
	अगर (ACPI_FAILURE(status)) अणु
		pr_debug("_ADR returned %d on %s\n",
			 status, (अक्षर *)buffer.poपूर्णांकer);
		जाओ out;
	पूर्ण

	/* No _SUN == not a slot == bail */
	status = acpi_evaluate_पूर्णांकeger(handle, "_SUN", शून्य, sun);
	अगर (ACPI_FAILURE(status)) अणु
		pr_debug("_SUN returned %d on %s\n",
			 status, (अक्षर *)buffer.poपूर्णांकer);
		जाओ out;
	पूर्ण

	device = (adr >> 16) & 0xffff;
out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस device;
पूर्ण

/*
 * Check whether handle has an associated slot and create PCI slot अगर it has.
 */
अटल acpi_status
रेजिस्टर_slot(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	पूर्णांक device;
	अचिन्हित दीर्घ दीर्घ sun;
	अक्षर name[SLOT_NAME_SIZE];
	काष्ठा acpi_pci_slot *slot;
	काष्ठा pci_slot *pci_slot;
	काष्ठा pci_bus *pci_bus = context;

	device = check_slot(handle, &sun);
	अगर (device < 0)
		वापस AE_OK;

	/*
	 * There may be multiple PCI functions associated with the same slot.
	 * Check whether PCI slot has alपढ़ोy been created क्रम this PCI device.
	 */
	list_क्रम_each_entry(slot, &slot_list, list) अणु
		pci_slot = slot->pci_slot;
		अगर (pci_slot->bus == pci_bus && pci_slot->number == device)
			वापस AE_OK;
	पूर्ण

	slot = kदो_स्मृति(माप(*slot), GFP_KERNEL);
	अगर (!slot)
		वापस AE_OK;

	snम_लिखो(name, माप(name), "%llu", sun);
	pci_slot = pci_create_slot(pci_bus, device, name, शून्य);
	अगर (IS_ERR(pci_slot)) अणु
		pr_err("pci_create_slot returned %ld\n", PTR_ERR(pci_slot));
		kमुक्त(slot);
		वापस AE_OK;
	पूर्ण

	slot->pci_slot = pci_slot;
	list_add(&slot->list, &slot_list);

	get_device(&pci_bus->dev);

	pr_debug("%p, pci_bus: %x, device: %d, name: %s\n",
		 pci_slot, pci_bus->number, device, name);

	वापस AE_OK;
पूर्ण

व्योम acpi_pci_slot_क्रमागतerate(काष्ठा pci_bus *bus)
अणु
	acpi_handle handle = ACPI_HANDLE(bus->bridge);

	अगर (handle) अणु
		mutex_lock(&slot_list_lock);
		acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				    रेजिस्टर_slot, शून्य, bus, शून्य);
		mutex_unlock(&slot_list_lock);
	पूर्ण
पूर्ण

व्योम acpi_pci_slot_हटाओ(काष्ठा pci_bus *bus)
अणु
	काष्ठा acpi_pci_slot *slot, *पंचांगp;

	mutex_lock(&slot_list_lock);
	list_क्रम_each_entry_safe(slot, पंचांगp, &slot_list, list) अणु
		अगर (slot->pci_slot->bus == bus) अणु
			list_del(&slot->list);
			pci_destroy_slot(slot->pci_slot);
			put_device(&bus->dev);
			kमुक्त(slot);
		पूर्ण
	पूर्ण
	mutex_unlock(&slot_list_lock);
पूर्ण

अटल पूर्णांक करो_sta_beक्रमe_sun(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_info("%s detected: will evaluate _STA before calling _SUN\n",
		d->ident);
	check_sta_beक्रमe_sun = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_pci_slot_dmi_table[] __initस्थिर = अणु
	/*
	 * Fujitsu Primequest machines will वापस 1023 to indicate an
	 * error अगर the _SUN method is evaluated on SxFy objects that
	 * are not present (as indicated by _STA), so क्रम those machines,
	 * we want to check _STA beक्रमe evaluating _SUN.
	 */
	अणु
	 .callback = करो_sta_beक्रमe_sun,
	 .ident = "Fujitsu PRIMEQUEST",
	 .matches = अणु
		DMI_MATCH(DMI_BIOS_VENDOR, "FUJITSU LIMITED"),
		DMI_MATCH(DMI_BIOS_VERSION, "PRIMEQUEST"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init acpi_pci_slot_init(व्योम)
अणु
	dmi_check_प्रणाली(acpi_pci_slot_dmi_table);
पूर्ण
