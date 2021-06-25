<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EFI_EMBEDDED_FW_H
#घोषणा _LINUX_EFI_EMBEDDED_FW_H

#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>

#घोषणा EFI_EMBEDDED_FW_PREFIX_LEN		8

/*
 * This काष्ठा is निजी to the efi-embedded fw implementation.
 * They are in this header क्रम use by lib/test_firmware.c only!
 */
काष्ठा efi_embedded_fw अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	स्थिर u8 *data;
	माप_प्रकार length;
पूर्ण;

/**
 * काष्ठा efi_embedded_fw_desc - This काष्ठा is used by the EFI embedded-fw
 *                               code to search क्रम embedded firmwares.
 *
 * @name:   Name to रेजिस्टर the firmware with अगर found
 * @prefix: First 8 bytes of the firmware
 * @length: Length of the firmware in bytes including prefix
 * @sha256: SHA256 of the firmware
 */
काष्ठा efi_embedded_fw_desc अणु
	स्थिर अक्षर *name;
	u8 prefix[EFI_EMBEDDED_FW_PREFIX_LEN];
	u32 length;
	u8 sha256[32];
पूर्ण;

बाह्य स्थिर काष्ठा dmi_प्रणाली_id touchscreen_dmi_table[];

पूर्णांक efi_get_embedded_fw(स्थिर अक्षर *name, स्थिर u8 **dat, माप_प्रकार *sz);

#पूर्ण_अगर
