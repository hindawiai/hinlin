<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम extracting embedded firmware क्रम peripherals from EFI code,
 *
 * Copyright (c) 2018 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/efi_embedded_fw.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <crypto/sha2.h>

/* Exported क्रम use by lib/test_firmware.c only */
LIST_HEAD(efi_embedded_fw_list);
EXPORT_SYMBOL_NS_GPL(efi_embedded_fw_list, TEST_FIRMWARE);
bool efi_embedded_fw_checked;
EXPORT_SYMBOL_NS_GPL(efi_embedded_fw_checked, TEST_FIRMWARE);

अटल स्थिर काष्ठा dmi_प्रणाली_id * स्थिर embedded_fw_table[] = अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_DMI
	touchscreen_dmi_table,
#पूर्ण_अगर
	शून्य
पूर्ण;

/*
 * Note the efi_check_क्रम_embedded_firmwares() code currently makes the
 * following 2 assumptions. This may needs to be revisited अगर embedded firmware
 * is found where this is not true:
 * 1) The firmware is only found in EFI_BOOT_SERVICES_CODE memory segments
 * 2) The firmware always starts at an offset which is a multiple of 8 bytes
 */
अटल पूर्णांक __init efi_check_md_क्रम_embedded_firmware(
	efi_memory_desc_t *md, स्थिर काष्ठा efi_embedded_fw_desc *desc)
अणु
	काष्ठा efi_embedded_fw *fw;
	u8 hash[32];
	u64 i, size;
	u8 *map;

	size = md->num_pages << EFI_PAGE_SHIFT;
	map = memremap(md->phys_addr, size, MEMREMAP_WB);
	अगर (!map) अणु
		pr_err("Error mapping EFI mem at %#llx\n", md->phys_addr);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; (i + desc->length) <= size; i += 8) अणु
		अगर (स_भेद(map + i, desc->prefix, EFI_EMBEDDED_FW_PREFIX_LEN))
			जारी;

		sha256(map + i, desc->length, hash);
		अगर (स_भेद(hash, desc->sha256, 32) == 0)
			अवरोध;
	पूर्ण
	अगर ((i + desc->length) > size) अणु
		memunmap(map);
		वापस -ENOENT;
	पूर्ण

	pr_info("Found EFI embedded fw '%s'\n", desc->name);

	fw = kदो_स्मृति(माप(*fw), GFP_KERNEL);
	अगर (!fw) अणु
		memunmap(map);
		वापस -ENOMEM;
	पूर्ण

	fw->data = kmemdup(map + i, desc->length, GFP_KERNEL);
	memunmap(map);
	अगर (!fw->data) अणु
		kमुक्त(fw);
		वापस -ENOMEM;
	पूर्ण

	fw->name = desc->name;
	fw->length = desc->length;
	list_add(&fw->list, &efi_embedded_fw_list);

	वापस 0;
पूर्ण

व्योम __init efi_check_क्रम_embedded_firmwares(व्योम)
अणु
	स्थिर काष्ठा efi_embedded_fw_desc *fw_desc;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	efi_memory_desc_t *md;
	पूर्णांक i, r;

	क्रम (i = 0; embedded_fw_table[i]; i++) अणु
		dmi_id = dmi_first_match(embedded_fw_table[i]);
		अगर (!dmi_id)
			जारी;

		fw_desc = dmi_id->driver_data;

		/*
		 * In some drivers the काष्ठा driver_data contains may contain
		 * other driver specअगरic data after the fw_desc काष्ठा; and
		 * the fw_desc काष्ठा itself may be empty, skip these.
		 */
		अगर (!fw_desc->name)
			जारी;

		क्रम_each_efi_memory_desc(md) अणु
			अगर (md->type != EFI_BOOT_SERVICES_CODE)
				जारी;

			r = efi_check_md_क्रम_embedded_firmware(md, fw_desc);
			अगर (r == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	efi_embedded_fw_checked = true;
पूर्ण

पूर्णांक efi_get_embedded_fw(स्थिर अक्षर *name, स्थिर u8 **data, माप_प्रकार *size)
अणु
	काष्ठा efi_embedded_fw *iter, *fw = शून्य;

	अगर (!efi_embedded_fw_checked) अणु
		pr_warn("Warning %s called while we did not check for embedded fw\n",
			__func__);
		वापस -ENOENT;
	पूर्ण

	list_क्रम_each_entry(iter, &efi_embedded_fw_list, list) अणु
		अगर (म_भेद(name, iter->name) == 0) अणु
			fw = iter;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!fw)
		वापस -ENOENT;

	*data = fw->data;
	*size = fw->length;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efi_get_embedded_fw);
