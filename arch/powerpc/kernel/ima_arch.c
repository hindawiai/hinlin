<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 */

#समावेश <linux/ima.h>
#समावेश <यंत्र/secure_boot.h>

bool arch_ima_get_secureboot(व्योम)
अणु
	वापस is_ppc_secureboot_enabled();
पूर्ण

/*
 * The "secure_rules" are enabled only on "secureboot" enabled प्रणालीs.
 * These rules verअगरy the file signatures against known good values.
 * The "appraise_type=imasig|modsig" option allows the known good signature
 * to be stored as an xattr or as an appended signature.
 *
 * To aव्योम duplicate signature verअगरication as much as possible, the IMA
 * policy rule क्रम module appraisal is added only अगर CONFIG_MODULE_SIG
 * is not enabled.
 */
अटल स्थिर अक्षर *स्थिर secure_rules[] = अणु
	"appraise func=KEXEC_KERNEL_CHECK appraise_flag=check_blacklist appraise_type=imasig|modsig",
#अगर_अघोषित CONFIG_MODULE_SIG
	"appraise func=MODULE_CHECK appraise_flag=check_blacklist appraise_type=imasig|modsig",
#पूर्ण_अगर
	शून्य
पूर्ण;

/*
 * The "trusted_rules" are enabled only on "trustedboot" enabled प्रणालीs.
 * These rules add the kexec kernel image and kernel modules file hashes to
 * the IMA measurement list.
 */
अटल स्थिर अक्षर *स्थिर trusted_rules[] = अणु
	"measure func=KEXEC_KERNEL_CHECK",
	"measure func=MODULE_CHECK",
	शून्य
पूर्ण;

/*
 * The "secure_and_trusted_rules" contains rules क्रम both the secure boot and
 * trusted boot. The "template=ima-modsig" option includes the appended
 * signature, when available, in the IMA measurement list.
 */
अटल स्थिर अक्षर *स्थिर secure_and_trusted_rules[] = अणु
	"measure func=KEXEC_KERNEL_CHECK template=ima-modsig",
	"measure func=MODULE_CHECK template=ima-modsig",
	"appraise func=KEXEC_KERNEL_CHECK appraise_flag=check_blacklist appraise_type=imasig|modsig",
#अगर_अघोषित CONFIG_MODULE_SIG
	"appraise func=MODULE_CHECK appraise_flag=check_blacklist appraise_type=imasig|modsig",
#पूर्ण_अगर
	शून्य
पूर्ण;

/*
 * Returns the relevant IMA arch-specअगरic policies based on the प्रणाली secure
 * boot state.
 */
स्थिर अक्षर *स्थिर *arch_get_ima_policy(व्योम)
अणु
	अगर (is_ppc_secureboot_enabled()) अणु
		अगर (IS_ENABLED(CONFIG_MODULE_SIG))
			set_module_sig_enक्रमced();

		अगर (is_ppc_trustedboot_enabled())
			वापस secure_and_trusted_rules;
		अन्यथा
			वापस secure_rules;
	पूर्ण अन्यथा अगर (is_ppc_trustedboot_enabled()) अणु
		वापस trusted_rules;
	पूर्ण

	वापस शून्य;
पूर्ण
