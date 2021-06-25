<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Intel Corporation; author Matt Fleming
 * Copyright (c) 2014 Red Hat, Inc., Mark Salter <msalter@redhat.com>
 */
#समावेश <linux/efi.h>
#समावेश <linux/reboot.h>

अटल व्योम (*orig_pm_घातer_off)(व्योम);

पूर्णांक efi_reboot_quirk_mode = -1;

व्योम efi_reboot(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *__unused)
अणु
	स्थिर अक्षर *str[] = अणु "cold", "warm", "shutdown", "platform" पूर्ण;
	पूर्णांक efi_mode, cap_reset_mode;

	अगर (!efi_rt_services_supported(EFI_RT_SUPPORTED_RESET_SYSTEM))
		वापस;

	चयन (reboot_mode) अणु
	हाल REBOOT_WARM:
	हाल REBOOT_SOFT:
		efi_mode = EFI_RESET_WARM;
		अवरोध;
	शेष:
		efi_mode = EFI_RESET_COLD;
		अवरोध;
	पूर्ण

	/*
	 * If a quirk क्रमced an EFI reset mode, always use that.
	 */
	अगर (efi_reboot_quirk_mode != -1)
		efi_mode = efi_reboot_quirk_mode;

	अगर (efi_capsule_pending(&cap_reset_mode)) अणु
		अगर (efi_mode != cap_reset_mode)
			prपूर्णांकk(KERN_CRIT "efi: %s reset requested but pending "
			       "capsule update requires %s reset... Performing "
			       "%s reset.\n", str[efi_mode], str[cap_reset_mode],
			       str[cap_reset_mode]);
		efi_mode = cap_reset_mode;
	पूर्ण

	efi.reset_प्रणाली(efi_mode, EFI_SUCCESS, 0, शून्य);
पूर्ण

bool __weak efi_घातeroff_required(व्योम)
अणु
	वापस false;
पूर्ण

अटल व्योम efi_घातer_off(व्योम)
अणु
	efi.reset_प्रणाली(EFI_RESET_SHUTDOWN, EFI_SUCCESS, 0, शून्य);
	/*
	 * The above call should not वापस, अगर it करोes fall back to
	 * the original घातer off method (typically ACPI घातeroff).
	 */
	अगर (orig_pm_घातer_off)
		orig_pm_घातer_off();
पूर्ण

अटल पूर्णांक __init efi_shutकरोwn_init(व्योम)
अणु
	अगर (!efi_rt_services_supported(EFI_RT_SUPPORTED_RESET_SYSTEM))
		वापस -ENODEV;

	अगर (efi_घातeroff_required()) अणु
		orig_pm_घातer_off = pm_घातer_off;
		pm_घातer_off = efi_घातer_off;
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(efi_shutकरोwn_init);
