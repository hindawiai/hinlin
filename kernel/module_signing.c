<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Module signature checker
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/module_signature.h>
#समावेश <linux/माला.स>
#समावेश <linux/verअगरication.h>
#समावेश <crypto/खुला_key.h>
#समावेश "module-internal.h"

/*
 * Verअगरy the signature on a module.
 */
पूर्णांक mod_verअगरy_sig(स्थिर व्योम *mod, काष्ठा load_info *info)
अणु
	काष्ठा module_signature ms;
	माप_प्रकार sig_len, modlen = info->len;
	पूर्णांक ret;

	pr_devel("==>%s(,%zu)\n", __func__, modlen);

	अगर (modlen <= माप(ms))
		वापस -EBADMSG;

	स_नकल(&ms, mod + (modlen - माप(ms)), माप(ms));

	ret = mod_check_sig(&ms, modlen, "module");
	अगर (ret)
		वापस ret;

	sig_len = be32_to_cpu(ms.sig_len);
	modlen -= sig_len + माप(ms);
	info->len = modlen;

	वापस verअगरy_pkcs7_signature(mod, modlen, mod + modlen, sig_len,
				      VERIFY_USE_SECONDARY_KEYRING,
				      VERIFYING_MODULE_SIGNATURE,
				      शून्य, शून्य);
पूर्ण
