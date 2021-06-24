<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Platक्रमm keyring क्रम firmware/platक्रमm keys
 *
 * Copyright IBM Corporation, 2018
 * Author(s): Nayna Jain <nayna@linux.ibm.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश "../integrity.h"

/**
 * add_to_platक्रमm_keyring - Add to platक्रमm keyring without validation.
 * @source: Source of key
 * @data: The blob holding the key
 * @len: The length of the data blob
 *
 * Add a key to the platक्रमm keyring without checking its trust chain.  This
 * is available only during kernel initialisation.
 */
व्योम __init add_to_platक्रमm_keyring(स्थिर अक्षर *source, स्थिर व्योम *data,
				    माप_प्रकार len)
अणु
	key_perm_t perm;
	पूर्णांक rc;

	perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_VIEW;

	rc = पूर्णांकegrity_load_cert(INTEGRITY_KEYRING_PLATFORM, source, data, len,
				 perm);
	अगर (rc)
		pr_info("Error adding keys to platform keyring %s\n", source);
पूर्ण

/*
 * Create the trusted keyrings.
 */
अटल __init पूर्णांक platक्रमm_keyring_init(व्योम)
अणु
	पूर्णांक rc;

	rc = पूर्णांकegrity_init_keyring(INTEGRITY_KEYRING_PLATFORM);
	अगर (rc)
		वापस rc;

	pr_notice("Platform Keyring initialized\n");
	वापस 0;
पूर्ण

/*
 * Must be initialised beक्रमe we try and load the keys पूर्णांकo the keyring.
 */
device_initcall(platक्रमm_keyring_init);
