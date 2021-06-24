<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * efibc: control EFI bootloaders which obey LoaderEntryOneShot var
 * Copyright (c) 2013-2016, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "efibc: " fmt

#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>

अटल व्योम efibc_str_to_str16(स्थिर अक्षर *str, efi_अक्षर16_t *str16)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < म_माप(str); i++)
		str16[i] = str[i];

	str16[i] = '\0';
पूर्ण

अटल पूर्णांक efibc_set_variable(स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	पूर्णांक ret;
	efi_guid_t guid = LINUX_EFI_LOADER_ENTRY_GUID;
	काष्ठा efivar_entry *entry;
	माप_प्रकार size = (म_माप(value) + 1) * माप(efi_अक्षर16_t);

	अगर (size > माप(entry->var.Data)) अणु
		pr_err("value is too large (%zu bytes) for '%s' EFI variable\n", size, name);
		वापस -EINVAL;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		pr_err("failed to allocate efivar entry for '%s' EFI variable\n", name);
		वापस -ENOMEM;
	पूर्ण

	efibc_str_to_str16(name, entry->var.VariableName);
	efibc_str_to_str16(value, (efi_अक्षर16_t *)entry->var.Data);
	स_नकल(&entry->var.VenकरोrGuid, &guid, माप(guid));

	ret = efivar_entry_set_safe(entry->var.VariableName,
				    entry->var.VenकरोrGuid,
				    EFI_VARIABLE_NON_VOLATILE
				    | EFI_VARIABLE_BOOTSERVICE_ACCESS
				    | EFI_VARIABLE_RUNTIME_ACCESS,
				    false, size, entry->var.Data);

	अगर (ret)
		pr_err("failed to set %s EFI variable: 0x%x\n",
		       name, ret);

	kमुक्त(entry);
	वापस ret;
पूर्ण

अटल पूर्णांक efibc_reboot_notअगरier_call(काष्ठा notअगरier_block *notअगरier,
				      अचिन्हित दीर्घ event, व्योम *data)
अणु
	स्थिर अक्षर *reason = "shutdown";
	पूर्णांक ret;

	अगर (event == SYS_RESTART)
		reason = "reboot";

	ret = efibc_set_variable("LoaderEntryRebootReason", reason);
	अगर (ret || !data)
		वापस NOTIFY_DONE;

	efibc_set_variable("LoaderEntryOneShot", (अक्षर *)data);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block efibc_reboot_notअगरier = अणु
	.notअगरier_call = efibc_reboot_notअगरier_call,
पूर्ण;

अटल पूर्णांक __init efibc_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!efivars_kobject() || !efivar_supports_ग_लिखोs())
		वापस -ENODEV;

	ret = रेजिस्टर_reboot_notअगरier(&efibc_reboot_notअगरier);
	अगर (ret)
		pr_err("unable to register reboot notifier\n");

	वापस ret;
पूर्ण
module_init(efibc_init);

अटल व्योम __निकास efibc_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&efibc_reboot_notअगरier);
पूर्ण
module_निकास(efibc_निकास);

MODULE_AUTHOR("Jeremy Compostella <jeremy.compostella@intel.com>");
MODULE_AUTHOR("Matt Gumbel <matthew.k.gumbel@intel.com");
MODULE_DESCRIPTION("EFI Bootloader Control");
MODULE_LICENSE("GPL v2");
