<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Instantiate a खुला key crypto key from an X.509 Certअगरicate
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "X.509: "fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <keys/asymmetric-subtype.h>
#समावेश <keys/asymmetric-parser.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश <crypto/hash.h>
#समावेश "asymmetric_keys.h"
#समावेश "x509_parser.h"

/*
 * Set up the signature parameters in an X.509 certअगरicate.  This involves
 * digesting the चिन्हित data and extracting the signature.
 */
पूर्णांक x509_get_sig_params(काष्ठा x509_certअगरicate *cert)
अणु
	काष्ठा खुला_key_signature *sig = cert->sig;
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;
	माप_प्रकार desc_size;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	sig->data = cert->tbs;
	sig->data_size = cert->tbs_size;

	अगर (!cert->pub->pkey_algo)
		cert->unsupported_key = true;

	अगर (!sig->pkey_algo)
		cert->unsupported_sig = true;

	/* We check the hash अगर we can - even अगर we can't then verअगरy it */
	अगर (!sig->hash_algo) अणु
		cert->unsupported_sig = true;
		वापस 0;
	पूर्ण

	sig->s = kmemdup(cert->raw_sig, cert->raw_sig_size, GFP_KERNEL);
	अगर (!sig->s)
		वापस -ENOMEM;

	sig->s_size = cert->raw_sig_size;

	/* Allocate the hashing algorithm we're going to need and find out how
	 * big the hash operational data will be.
	 */
	tfm = crypto_alloc_shash(sig->hash_algo, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		अगर (PTR_ERR(tfm) == -ENOENT) अणु
			cert->unsupported_sig = true;
			वापस 0;
		पूर्ण
		वापस PTR_ERR(tfm);
	पूर्ण

	desc_size = crypto_shash_descsize(tfm) + माप(*desc);
	sig->digest_size = crypto_shash_digestsize(tfm);

	ret = -ENOMEM;
	sig->digest = kदो_स्मृति(sig->digest_size, GFP_KERNEL);
	अगर (!sig->digest)
		जाओ error;

	desc = kzalloc(desc_size, GFP_KERNEL);
	अगर (!desc)
		जाओ error;

	desc->tfm = tfm;

	ret = crypto_shash_digest(desc, cert->tbs, cert->tbs_size, sig->digest);
	अगर (ret < 0)
		जाओ error_2;

	ret = is_hash_blacklisted(sig->digest, sig->digest_size, "tbs");
	अगर (ret == -EKEYREJECTED) अणु
		pr_err("Cert %*phN is blacklisted\n",
		       sig->digest_size, sig->digest);
		cert->blacklisted = true;
		ret = 0;
	पूर्ण

error_2:
	kमुक्त(desc);
error:
	crypto_मुक्त_shash(tfm);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Check क्रम self-चिन्हितness in an X.509 cert and अगर found, check the signature
 * immediately अगर we can.
 */
पूर्णांक x509_check_क्रम_self_चिन्हित(काष्ठा x509_certअगरicate *cert)
अणु
	पूर्णांक ret = 0;

	pr_devel("==>%s()\n", __func__);

	अगर (cert->raw_subject_size != cert->raw_issuer_size ||
	    स_भेद(cert->raw_subject, cert->raw_issuer,
		   cert->raw_issuer_size) != 0)
		जाओ not_self_चिन्हित;

	अगर (cert->sig->auth_ids[0] || cert->sig->auth_ids[1]) अणु
		/* If the AKID is present it may have one or two parts.  If
		 * both are supplied, both must match.
		 */
		bool a = asymmetric_key_id_same(cert->skid, cert->sig->auth_ids[1]);
		bool b = asymmetric_key_id_same(cert->id, cert->sig->auth_ids[0]);

		अगर (!a && !b)
			जाओ not_self_चिन्हित;

		ret = -EKEYREJECTED;
		अगर (((a && !b) || (b && !a)) &&
		    cert->sig->auth_ids[0] && cert->sig->auth_ids[1])
			जाओ out;
	पूर्ण

	ret = -EKEYREJECTED;
	अगर (म_भेद(cert->pub->pkey_algo, cert->sig->pkey_algo) != 0 &&
	    (म_भेदन(cert->pub->pkey_algo, "ecdsa-", 6) != 0 ||
	     म_भेद(cert->sig->pkey_algo, "ecdsa") != 0))
		जाओ out;

	ret = खुला_key_verअगरy_signature(cert->pub, cert->sig);
	अगर (ret < 0) अणु
		अगर (ret == -ENOPKG) अणु
			cert->unsupported_sig = true;
			ret = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	pr_devel("Cert Self-signature verified");
	cert->self_चिन्हित = true;

out:
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;

not_self_चिन्हित:
	pr_devel("<==%s() = 0 [not]\n", __func__);
	वापस 0;
पूर्ण

/*
 * Attempt to parse a data blob क्रम a key as an X509 certअगरicate.
 */
अटल पूर्णांक x509_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा asymmetric_key_ids *kids;
	काष्ठा x509_certअगरicate *cert;
	स्थिर अक्षर *q;
	माप_प्रकार srlen, sulen;
	अक्षर *desc = शून्य, *p;
	पूर्णांक ret;

	cert = x509_cert_parse(prep->data, prep->datalen);
	अगर (IS_ERR(cert))
		वापस PTR_ERR(cert);

	pr_devel("Cert Issuer: %s\n", cert->issuer);
	pr_devel("Cert Subject: %s\n", cert->subject);

	अगर (cert->unsupported_key) अणु
		ret = -ENOPKG;
		जाओ error_मुक्त_cert;
	पूर्ण

	pr_devel("Cert Key Algo: %s\n", cert->pub->pkey_algo);
	pr_devel("Cert Valid period: %lld-%lld\n", cert->valid_from, cert->valid_to);

	cert->pub->id_type = "X509";

	अगर (cert->unsupported_sig) अणु
		खुला_key_signature_मुक्त(cert->sig);
		cert->sig = शून्य;
	पूर्ण अन्यथा अणु
		pr_devel("Cert Signature: %s + %s\n",
			 cert->sig->pkey_algo, cert->sig->hash_algo);
	पूर्ण

	/* Don't permit addition of blacklisted keys */
	ret = -EKEYREJECTED;
	अगर (cert->blacklisted)
		जाओ error_मुक्त_cert;

	/* Propose a description */
	sulen = म_माप(cert->subject);
	अगर (cert->raw_skid) अणु
		srlen = cert->raw_skid_size;
		q = cert->raw_skid;
	पूर्ण अन्यथा अणु
		srlen = cert->raw_serial_size;
		q = cert->raw_serial;
	पूर्ण

	ret = -ENOMEM;
	desc = kदो_स्मृति(sulen + 2 + srlen * 2 + 1, GFP_KERNEL);
	अगर (!desc)
		जाओ error_मुक्त_cert;
	p = स_नकल(desc, cert->subject, sulen);
	p += sulen;
	*p++ = ':';
	*p++ = ' ';
	p = bin2hex(p, q, srlen);
	*p = 0;

	kids = kदो_स्मृति(माप(काष्ठा asymmetric_key_ids), GFP_KERNEL);
	अगर (!kids)
		जाओ error_मुक्त_desc;
	kids->id[0] = cert->id;
	kids->id[1] = cert->skid;

	/* We're pinning the module by being linked against it */
	__module_get(खुला_key_subtype.owner);
	prep->payload.data[asym_subtype] = &खुला_key_subtype;
	prep->payload.data[asym_key_ids] = kids;
	prep->payload.data[asym_crypto] = cert->pub;
	prep->payload.data[asym_auth] = cert->sig;
	prep->description = desc;
	prep->quotalen = 100;

	/* We've finished with the certअगरicate */
	cert->pub = शून्य;
	cert->id = शून्य;
	cert->skid = शून्य;
	cert->sig = शून्य;
	desc = शून्य;
	ret = 0;

error_मुक्त_desc:
	kमुक्त(desc);
error_मुक्त_cert:
	x509_मुक्त_certअगरicate(cert);
	वापस ret;
पूर्ण

अटल काष्ठा asymmetric_key_parser x509_key_parser = अणु
	.owner	= THIS_MODULE,
	.name	= "x509",
	.parse	= x509_key_preparse,
पूर्ण;

/*
 * Module stuff
 */
अटल पूर्णांक __init x509_key_init(व्योम)
अणु
	वापस रेजिस्टर_asymmetric_key_parser(&x509_key_parser);
पूर्ण

अटल व्योम __निकास x509_key_निकास(व्योम)
अणु
	unरेजिस्टर_asymmetric_key_parser(&x509_key_parser);
पूर्ण

module_init(x509_key_init);
module_निकास(x509_key_निकास);

MODULE_DESCRIPTION("X.509 certificate parser");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");
