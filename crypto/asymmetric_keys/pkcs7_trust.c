<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Validate the trust chain of a PKCS#7 message.
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PKCS7: "fmt
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/asn1.h>
#समावेश <linux/key.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <crypto/खुला_key.h>
#समावेश "pkcs7_parser.h"

/*
 * Check the trust on one PKCS#7 SignedInfo block.
 */
अटल पूर्णांक pkcs7_validate_trust_one(काष्ठा pkcs7_message *pkcs7,
				    काष्ठा pkcs7_चिन्हित_info *sinfo,
				    काष्ठा key *trust_keyring)
अणु
	काष्ठा खुला_key_signature *sig = sinfo->sig;
	काष्ठा x509_certअगरicate *x509, *last = शून्य, *p;
	काष्ठा key *key;
	पूर्णांक ret;

	kenter(",%u,", sinfo->index);

	अगर (sinfo->unsupported_crypto) अणु
		kleave(" = -ENOPKG [cached]");
		वापस -ENOPKG;
	पूर्ण

	क्रम (x509 = sinfo->signer; x509; x509 = x509->signer) अणु
		अगर (x509->seen) अणु
			अगर (x509->verअगरied)
				जाओ verअगरied;
			kleave(" = -ENOKEY [cached]");
			वापस -ENOKEY;
		पूर्ण
		x509->seen = true;

		/* Look to see अगर this certअगरicate is present in the trusted
		 * keys.
		 */
		key = find_asymmetric_key(trust_keyring,
					  x509->id, x509->skid, false);
		अगर (!IS_ERR(key)) अणु
			/* One of the X.509 certअगरicates in the PKCS#7 message
			 * is apparently the same as one we alपढ़ोy trust.
			 * Verअगरy that the trusted variant can also validate
			 * the signature on the descendant.
			 */
			pr_devel("sinfo %u: Cert %u as key %x\n",
				 sinfo->index, x509->index, key_serial(key));
			जाओ matched;
		पूर्ण
		अगर (key == ERR_PTR(-ENOMEM))
			वापस -ENOMEM;

		 /* Self-चिन्हित certअगरicates क्रमm roots of their own, and अगर we
		  * करोn't know them, then we can't accept them.
		  */
		अगर (x509->signer == x509) अणु
			kleave(" = -ENOKEY [unknown self-signed]");
			वापस -ENOKEY;
		पूर्ण

		might_sleep();
		last = x509;
		sig = last->sig;
	पूर्ण

	/* No match - see अगर the root certअगरicate has a signer amongst the
	 * trusted keys.
	 */
	अगर (last && (last->sig->auth_ids[0] || last->sig->auth_ids[1])) अणु
		key = find_asymmetric_key(trust_keyring,
					  last->sig->auth_ids[0],
					  last->sig->auth_ids[1],
					  false);
		अगर (!IS_ERR(key)) अणु
			x509 = last;
			pr_devel("sinfo %u: Root cert %u signer is key %x\n",
				 sinfo->index, x509->index, key_serial(key));
			जाओ matched;
		पूर्ण
		अगर (PTR_ERR(key) != -ENOKEY)
			वापस PTR_ERR(key);
	पूर्ण

	/* As a last resort, see अगर we have a trusted खुला key that matches
	 * the चिन्हित info directly.
	 */
	key = find_asymmetric_key(trust_keyring,
				  sinfo->sig->auth_ids[0], शून्य, false);
	अगर (!IS_ERR(key)) अणु
		pr_devel("sinfo %u: Direct signer is key %x\n",
			 sinfo->index, key_serial(key));
		x509 = शून्य;
		sig = sinfo->sig;
		जाओ matched;
	पूर्ण
	अगर (PTR_ERR(key) != -ENOKEY)
		वापस PTR_ERR(key);

	kleave(" = -ENOKEY [no backref]");
	वापस -ENOKEY;

matched:
	ret = verअगरy_signature(key, sig);
	key_put(key);
	अगर (ret < 0) अणु
		अगर (ret == -ENOMEM)
			वापस ret;
		kleave(" = -EKEYREJECTED [verify %d]", ret);
		वापस -EKEYREJECTED;
	पूर्ण

verअगरied:
	अगर (x509) अणु
		x509->verअगरied = true;
		क्रम (p = sinfo->signer; p != x509; p = p->signer)
			p->verअगरied = true;
	पूर्ण
	kleave(" = 0");
	वापस 0;
पूर्ण

/**
 * pkcs7_validate_trust - Validate PKCS#7 trust chain
 * @pkcs7: The PKCS#7 certअगरicate to validate
 * @trust_keyring: Signing certअगरicates to use as starting poपूर्णांकs
 *
 * Validate that the certअगरicate chain inside the PKCS#7 message पूर्णांकersects
 * keys we alपढ़ोy know and trust.
 *
 * Returns, in order of descending priority:
 *
 *  (*) -EKEYREJECTED अगर a signature failed to match क्रम which we have a valid
 *	key, or:
 *
 *  (*) 0 अगर at least one signature chain पूर्णांकersects with the keys in the trust
 *	keyring, or:
 *
 *  (*) -ENOPKG अगर a suitable crypto module couldn't be found क्रम a check on a
 *	chain.
 *
 *  (*) -ENOKEY अगर we couldn't find a match क्रम any of the signature chains in
 *	the message.
 *
 * May also वापस -ENOMEM.
 */
पूर्णांक pkcs7_validate_trust(काष्ठा pkcs7_message *pkcs7,
			 काष्ठा key *trust_keyring)
अणु
	काष्ठा pkcs7_चिन्हित_info *sinfo;
	काष्ठा x509_certअगरicate *p;
	पूर्णांक cached_ret = -ENOKEY;
	पूर्णांक ret;

	क्रम (p = pkcs7->certs; p; p = p->next)
		p->seen = false;

	क्रम (sinfo = pkcs7->चिन्हित_infos; sinfo; sinfo = sinfo->next) अणु
		ret = pkcs7_validate_trust_one(pkcs7, sinfo, trust_keyring);
		चयन (ret) अणु
		हाल -ENOKEY:
			जारी;
		हाल -ENOPKG:
			अगर (cached_ret == -ENOKEY)
				cached_ret = -ENOPKG;
			जारी;
		हाल 0:
			cached_ret = 0;
			जारी;
		शेष:
			वापस ret;
		पूर्ण
	पूर्ण

	वापस cached_ret;
पूर्ण
EXPORT_SYMBOL_GPL(pkcs7_validate_trust);
