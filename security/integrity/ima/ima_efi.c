<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 IBM Corporation
 */
#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/ima.h>
#समावेश <यंत्र/efi.h>

#अगर_अघोषित arch_ima_efi_boot_mode
#घोषणा arch_ima_efi_boot_mode efi_secureboot_mode_unset
#पूर्ण_अगर

अटल क्रमागत efi_secureboot_mode get_sb_mode(व्योम)
अणु
	क्रमागत efi_secureboot_mode mode;

	अगर (!efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE)) अणु
		pr_info("ima: secureboot mode unknown, no efi\n");
		वापस efi_secureboot_mode_unknown;
	पूर्ण

	mode = efi_get_secureboot_mode(efi.get_variable);
	अगर (mode == efi_secureboot_mode_disabled)
		pr_info("ima: secureboot mode disabled\n");
	अन्यथा अगर (mode == efi_secureboot_mode_unknown)
		pr_info("ima: secureboot mode unknown\n");
	अन्यथा
		pr_info("ima: secureboot mode enabled\n");
	वापस mode;
पूर्ण

bool arch_ima_get_secureboot(व्योम)
अणु
	अटल क्रमागत efi_secureboot_mode sb_mode;
	अटल bool initialized;

	अगर (!initialized && efi_enabled(EFI_BOOT)) अणु
		sb_mode = arch_ima_efi_boot_mode;

		अगर (sb_mode == efi_secureboot_mode_unset)
			sb_mode = get_sb_mode();
		initialized = true;
	पूर्ण

	अगर (sb_mode == efi_secureboot_mode_enabled)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* secureboot arch rules */
अटल स्थिर अक्षर * स्थिर sb_arch_rules[] = अणु
#अगर !IS_ENABLED(CONFIG_KEXEC_SIG)
	"appraise func=KEXEC_KERNEL_CHECK appraise_type=imasig",
#पूर्ण_अगर /* CONFIG_KEXEC_SIG */
	"measure func=KEXEC_KERNEL_CHECK",
#अगर !IS_ENABLED(CONFIG_MODULE_SIG)
	"appraise func=MODULE_CHECK appraise_type=imasig",
#पूर्ण_अगर
	"measure func=MODULE_CHECK",
	शून्य
पूर्ण;

स्थिर अक्षर * स्थिर *arch_get_ima_policy(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_IMA_ARCH_POLICY) && arch_ima_get_secureboot()) अणु
		अगर (IS_ENABLED(CONFIG_MODULE_SIG))
			set_module_sig_enक्रमced();
		वापस sb_arch_rules;
	पूर्ण
	वापस शून्य;
पूर्ण
