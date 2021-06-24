<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Secure boot handling.
 *
 * Copyright (C) 2013,2014 Linaro Limited
 *     Roy Franz <roy.franz@linaro.org
 * Copyright (C) 2013 Red Hat, Inc.
 *     Mark Salter <msalter@redhat.com>
 */
#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

/* SHIM variables */
अटल स्थिर efi_guid_t shim_guid = EFI_SHIM_LOCK_GUID;
अटल स्थिर efi_अक्षर16_t shim_MokSBState_name[] = L"MokSBState";

अटल efi_status_t get_var(efi_अक्षर16_t *name, efi_guid_t *venकरोr, u32 *attr,
			    अचिन्हित दीर्घ *data_size, व्योम *data)
अणु
	वापस get_efi_var(name, venकरोr, attr, data_size, data);
पूर्ण

/*
 * Determine whether we're in secure boot mode.
 */
क्रमागत efi_secureboot_mode efi_get_secureboot(व्योम)
अणु
	u32 attr;
	अचिन्हित दीर्घ size;
	क्रमागत efi_secureboot_mode mode;
	efi_status_t status;
	u8 moksbstate;

	mode = efi_get_secureboot_mode(get_var);
	अगर (mode == efi_secureboot_mode_unknown) अणु
		efi_err("Could not determine UEFI Secure Boot status.\n");
		वापस efi_secureboot_mode_unknown;
	पूर्ण
	अगर (mode != efi_secureboot_mode_enabled)
		वापस mode;

	/*
	 * See अगर a user has put the shim पूर्णांकo insecure mode. If so, and अगर the
	 * variable करोesn't have the runसमय attribute set, we might as well
	 * honor that.
	 */
	size = माप(moksbstate);
	status = get_efi_var(shim_MokSBState_name, &shim_guid,
			     &attr, &size, &moksbstate);

	/* If it fails, we करोn't care why. Default to secure */
	अगर (status != EFI_SUCCESS)
		जाओ secure_boot_enabled;
	अगर (!(attr & EFI_VARIABLE_RUNTIME_ACCESS) && moksbstate == 1)
		वापस efi_secureboot_mode_disabled;

secure_boot_enabled:
	efi_info("UEFI Secure Boot is enabled.\n");
	वापस efi_secureboot_mode_enabled;
पूर्ण
