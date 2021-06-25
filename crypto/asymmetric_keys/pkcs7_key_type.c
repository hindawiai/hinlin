<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Testing module to load key from trusted PKCS#7 message
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PKCS7key: "fmt
#समावेश <linux/key.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/verअगरication.h>
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PKCS#7 testing key type");
MODULE_AUTHOR("Red Hat, Inc.");

अटल अचिन्हित pkcs7_usage;
module_param_named(usage, pkcs7_usage, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(pkcs7_usage,
		 "Usage to specify when verifying the PKCS#7 message");

/*
 * Retrieve the PKCS#7 message content.
 */
अटल पूर्णांक pkcs7_view_content(व्योम *ctx, स्थिर व्योम *data, माप_प्रकार len,
			      माप_प्रकार asn1hdrlen)
अणु
	काष्ठा key_preparsed_payload *prep = ctx;
	स्थिर व्योम *saved_prep_data;
	माप_प्रकार saved_prep_datalen;
	पूर्णांक ret;

	saved_prep_data = prep->data;
	saved_prep_datalen = prep->datalen;
	prep->data = data;
	prep->datalen = len;

	ret = user_preparse(prep);

	prep->data = saved_prep_data;
	prep->datalen = saved_prep_datalen;
	वापस ret;
पूर्ण

/*
 * Preparse a PKCS#7 wrapped and validated data blob.
 */
अटल पूर्णांक pkcs7_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	क्रमागत key_being_used_क्रम usage = pkcs7_usage;

	अगर (usage >= NR__KEY_BEING_USED_FOR) अणु
		pr_err("Invalid usage type %d\n", usage);
		वापस -EINVAL;
	पूर्ण

	वापस verअगरy_pkcs7_signature(शून्य, 0,
				      prep->data, prep->datalen,
				      VERIFY_USE_SECONDARY_KEYRING, usage,
				      pkcs7_view_content, prep);
पूर्ण

/*
 * user defined keys take an arbitrary string as the description and an
 * arbitrary blob of data as the payload
 */
अटल काष्ठा key_type key_type_pkcs7 = अणु
	.name			= "pkcs7_test",
	.preparse		= pkcs7_preparse,
	.मुक्त_preparse		= user_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.revoke			= user_revoke,
	.destroy		= user_destroy,
	.describe		= user_describe,
	.पढ़ो			= user_पढ़ो,
पूर्ण;

/*
 * Module stuff
 */
अटल पूर्णांक __init pkcs7_key_init(व्योम)
अणु
	वापस रेजिस्टर_key_type(&key_type_pkcs7);
पूर्ण

अटल व्योम __निकास pkcs7_key_cleanup(व्योम)
अणु
	unरेजिस्टर_key_type(&key_type_pkcs7);
पूर्ण

module_init(pkcs7_key_init);
module_निकास(pkcs7_key_cleanup);
