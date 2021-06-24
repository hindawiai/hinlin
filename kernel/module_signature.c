<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Module signature checker
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/module_signature.h>
#समावेश <यंत्र/byteorder.h>

/**
 * mod_check_sig - check that the given signature is sane
 *
 * @ms:		Signature to check.
 * @file_len:	Size of the file to which @ms is appended.
 * @name:	What is being checked. Used क्रम error messages.
 */
पूर्णांक mod_check_sig(स्थिर काष्ठा module_signature *ms, माप_प्रकार file_len,
		  स्थिर अक्षर *name)
अणु
	अगर (be32_to_cpu(ms->sig_len) >= file_len - माप(*ms))
		वापस -EBADMSG;

	अगर (ms->id_type != PKEY_ID_PKCS7) अणु
		pr_err("%s: not signed with expected PKCS#7 message\n",
		       name);
		वापस -ENOPKG;
	पूर्ण

	अगर (ms->algo != 0 ||
	    ms->hash != 0 ||
	    ms->signer_len != 0 ||
	    ms->key_id_len != 0 ||
	    ms->__pad[0] != 0 ||
	    ms->__pad[1] != 0 ||
	    ms->__pad[2] != 0) अणु
		pr_err("%s: PKCS#7 signature info has unexpected non-zero params\n",
		       name);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण
