<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Verअगरy the signature on a PKCS#7 message.
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
#समावेश <crypto/hash.h>
#समावेश <crypto/hash_info.h>
#समावेश <crypto/खुला_key.h>
#समावेश "pkcs7_parser.h"

/*
 * Digest the relevant parts of the PKCS#7 data
 */
अटल पूर्णांक pkcs7_digest(काष्ठा pkcs7_message *pkcs7,
			काष्ठा pkcs7_चिन्हित_info *sinfo)
अणु
	काष्ठा खुला_key_signature *sig = sinfo->sig;
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;
	माप_प्रकार desc_size;
	पूर्णांक ret;

	kenter(",%u,%s", sinfo->index, sinfo->sig->hash_algo);

	/* The digest was calculated alपढ़ोy. */
	अगर (sig->digest)
		वापस 0;

	अगर (!sinfo->sig->hash_algo)
		वापस -ENOPKG;

	/* Allocate the hashing algorithm we're going to need and find out how
	 * big the hash operational data will be.
	 */
	tfm = crypto_alloc_shash(sinfo->sig->hash_algo, 0, 0);
	अगर (IS_ERR(tfm))
		वापस (PTR_ERR(tfm) == -ENOENT) ? -ENOPKG : PTR_ERR(tfm);

	desc_size = crypto_shash_descsize(tfm) + माप(*desc);
	sig->digest_size = crypto_shash_digestsize(tfm);

	ret = -ENOMEM;
	sig->digest = kदो_स्मृति(sig->digest_size, GFP_KERNEL);
	अगर (!sig->digest)
		जाओ error_no_desc;

	desc = kzalloc(desc_size, GFP_KERNEL);
	अगर (!desc)
		जाओ error_no_desc;

	desc->tfm   = tfm;

	/* Digest the message [RFC2315 9.3] */
	ret = crypto_shash_digest(desc, pkcs7->data, pkcs7->data_len,
				  sig->digest);
	अगर (ret < 0)
		जाओ error;
	pr_devel("MsgDigest = [%*ph]\n", 8, sig->digest);

	/* However, अगर there are authenticated attributes, there must be a
	 * message digest attribute amongst them which corresponds to the
	 * digest we just calculated.
	 */
	अगर (sinfo->authattrs) अणु
		u8 tag;

		अगर (!sinfo->msgdigest) अणु
			pr_warn("Sig %u: No messageDigest\n", sinfo->index);
			ret = -EKEYREJECTED;
			जाओ error;
		पूर्ण

		अगर (sinfo->msgdigest_len != sig->digest_size) अणु
			pr_debug("Sig %u: Invalid digest size (%u)\n",
				 sinfo->index, sinfo->msgdigest_len);
			ret = -EBADMSG;
			जाओ error;
		पूर्ण

		अगर (स_भेद(sig->digest, sinfo->msgdigest,
			   sinfo->msgdigest_len) != 0) अणु
			pr_debug("Sig %u: Message digest doesn't match\n",
				 sinfo->index);
			ret = -EKEYREJECTED;
			जाओ error;
		पूर्ण

		/* We then calculate anew, using the authenticated attributes
		 * as the contents of the digest instead.  Note that we need to
		 * convert the attributes from a CONT.0 पूर्णांकo a SET beक्रमe we
		 * hash it.
		 */
		स_रखो(sig->digest, 0, sig->digest_size);

		ret = crypto_shash_init(desc);
		अगर (ret < 0)
			जाओ error;
		tag = ASN1_CONS_BIT | ASN1_SET;
		ret = crypto_shash_update(desc, &tag, 1);
		अगर (ret < 0)
			जाओ error;
		ret = crypto_shash_finup(desc, sinfo->authattrs,
					 sinfo->authattrs_len, sig->digest);
		अगर (ret < 0)
			जाओ error;
		pr_devel("AADigest = [%*ph]\n", 8, sig->digest);
	पूर्ण

error:
	kमुक्त(desc);
error_no_desc:
	crypto_मुक्त_shash(tfm);
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

पूर्णांक pkcs7_get_digest(काष्ठा pkcs7_message *pkcs7, स्थिर u8 **buf, u32 *len,
		     क्रमागत hash_algo *hash_algo)
अणु
	काष्ठा pkcs7_चिन्हित_info *sinfo = pkcs7->चिन्हित_infos;
	पूर्णांक i, ret;

	/*
	 * This function करोesn't support messages with more than one signature.
	 */
	अगर (sinfo == शून्य || sinfo->next != शून्य)
		वापस -EBADMSG;

	ret = pkcs7_digest(pkcs7, sinfo);
	अगर (ret)
		वापस ret;

	*buf = sinfo->sig->digest;
	*len = sinfo->sig->digest_size;

	i = match_string(hash_algo_name, HASH_ALGO__LAST,
			 sinfo->sig->hash_algo);
	अगर (i >= 0)
		*hash_algo = i;

	वापस 0;
पूर्ण

/*
 * Find the key (X.509 certअगरicate) to use to verअगरy a PKCS#7 message.  PKCS#7
 * uses the issuer's name and the issuing certअगरicate serial number क्रम
 * matching purposes.  These must match the certअगरicate issuer's name (not
 * subject's name) and the certअगरicate serial number [RFC 2315 6.7].
 */
अटल पूर्णांक pkcs7_find_key(काष्ठा pkcs7_message *pkcs7,
			  काष्ठा pkcs7_चिन्हित_info *sinfo)
अणु
	काष्ठा x509_certअगरicate *x509;
	अचिन्हित certix = 1;

	kenter("%u", sinfo->index);

	क्रम (x509 = pkcs7->certs; x509; x509 = x509->next, certix++) अणु
		/* I'm _assuming_ that the generator of the PKCS#7 message will
		 * encode the fields from the X.509 cert in the same way in the
		 * PKCS#7 message - but I can't be 100% sure of that.  It's
		 * possible this will need element-by-element comparison.
		 */
		अगर (!asymmetric_key_id_same(x509->id, sinfo->sig->auth_ids[0]))
			जारी;
		pr_devel("Sig %u: Found cert serial match X.509[%u]\n",
			 sinfo->index, certix);

		अगर (म_भेद(x509->pub->pkey_algo, sinfo->sig->pkey_algo) != 0) अणु
			pr_warn("Sig %u: X.509 algo and PKCS#7 sig algo don't match\n",
				sinfo->index);
			जारी;
		पूर्ण

		sinfo->signer = x509;
		वापस 0;
	पूर्ण

	/* The relevant X.509 cert isn't found here, but it might be found in
	 * the trust keyring.
	 */
	pr_debug("Sig %u: Issuing X.509 cert not found (#%*phN)\n",
		 sinfo->index,
		 sinfo->sig->auth_ids[0]->len, sinfo->sig->auth_ids[0]->data);
	वापस 0;
पूर्ण

/*
 * Verअगरy the पूर्णांकernal certअगरicate chain as best we can.
 */
अटल पूर्णांक pkcs7_verअगरy_sig_chain(काष्ठा pkcs7_message *pkcs7,
				  काष्ठा pkcs7_चिन्हित_info *sinfo)
अणु
	काष्ठा खुला_key_signature *sig;
	काष्ठा x509_certअगरicate *x509 = sinfo->signer, *p;
	काष्ठा asymmetric_key_id *auth;
	पूर्णांक ret;

	kenter("");

	क्रम (p = pkcs7->certs; p; p = p->next)
		p->seen = false;

	क्रम (;;) अणु
		pr_debug("verify %s: %*phN\n",
			 x509->subject,
			 x509->raw_serial_size, x509->raw_serial);
		x509->seen = true;

		अगर (x509->blacklisted) अणु
			/* If this cert is blacklisted, then mark everything
			 * that depends on this as blacklisted too.
			 */
			sinfo->blacklisted = true;
			क्रम (p = sinfo->signer; p != x509; p = p->signer)
				p->blacklisted = true;
			pr_debug("- blacklisted\n");
			वापस 0;
		पूर्ण

		अगर (x509->unsupported_key)
			जाओ unsupported_crypto_in_x509;

		pr_debug("- issuer %s\n", x509->issuer);
		sig = x509->sig;
		अगर (sig->auth_ids[0])
			pr_debug("- authkeyid.id %*phN\n",
				 sig->auth_ids[0]->len, sig->auth_ids[0]->data);
		अगर (sig->auth_ids[1])
			pr_debug("- authkeyid.skid %*phN\n",
				 sig->auth_ids[1]->len, sig->auth_ids[1]->data);

		अगर (x509->self_चिन्हित) अणु
			/* If there's no authority certअगरicate specअगरied, then
			 * the certअगरicate must be self-चिन्हित and is the root
			 * of the chain.  Likewise अगर the cert is its own
			 * authority.
			 */
			अगर (x509->unsupported_sig)
				जाओ unsupported_crypto_in_x509;
			x509->signer = x509;
			pr_debug("- self-signed\n");
			वापस 0;
		पूर्ण

		/* Look through the X.509 certअगरicates in the PKCS#7 message's
		 * list to see अगर the next one is there.
		 */
		auth = sig->auth_ids[0];
		अगर (auth) अणु
			pr_debug("- want %*phN\n", auth->len, auth->data);
			क्रम (p = pkcs7->certs; p; p = p->next) अणु
				pr_debug("- cmp [%u] %*phN\n",
					 p->index, p->id->len, p->id->data);
				अगर (asymmetric_key_id_same(p->id, auth))
					जाओ found_issuer_check_skid;
			पूर्ण
		पूर्ण अन्यथा अगर (sig->auth_ids[1]) अणु
			auth = sig->auth_ids[1];
			pr_debug("- want %*phN\n", auth->len, auth->data);
			क्रम (p = pkcs7->certs; p; p = p->next) अणु
				अगर (!p->skid)
					जारी;
				pr_debug("- cmp [%u] %*phN\n",
					 p->index, p->skid->len, p->skid->data);
				अगर (asymmetric_key_id_same(p->skid, auth))
					जाओ found_issuer;
			पूर्ण
		पूर्ण

		/* We didn't find the root of this chain */
		pr_debug("- top\n");
		वापस 0;

	found_issuer_check_skid:
		/* We matched issuer + serialNumber, but अगर there's an
		 * authKeyId.keyId, that must match the CA subjKeyId also.
		 */
		अगर (sig->auth_ids[1] &&
		    !asymmetric_key_id_same(p->skid, sig->auth_ids[1])) अणु
			pr_warn("Sig %u: X.509 chain contains auth-skid nonmatch (%u->%u)\n",
				sinfo->index, x509->index, p->index);
			वापस -EKEYREJECTED;
		पूर्ण
	found_issuer:
		pr_debug("- subject %s\n", p->subject);
		अगर (p->seen) अणु
			pr_warn("Sig %u: X.509 chain contains loop\n",
				sinfo->index);
			वापस 0;
		पूर्ण
		ret = खुला_key_verअगरy_signature(p->pub, x509->sig);
		अगर (ret < 0)
			वापस ret;
		x509->signer = p;
		अगर (x509 == p) अणु
			pr_debug("- self-signed\n");
			वापस 0;
		पूर्ण
		x509 = p;
		might_sleep();
	पूर्ण

unsupported_crypto_in_x509:
	/* Just prune the certअगरicate chain at this poपूर्णांक अगर we lack some
	 * crypto module to go further.  Note, however, we करोn't want to set
	 * sinfo->unsupported_crypto as the चिन्हित info block may still be
	 * validatable against an X.509 cert lower in the chain that we have a
	 * trusted copy of.
	 */
	वापस 0;
पूर्ण

/*
 * Verअगरy one चिन्हित inक्रमmation block from a PKCS#7 message.
 */
अटल पूर्णांक pkcs7_verअगरy_one(काष्ठा pkcs7_message *pkcs7,
			    काष्ठा pkcs7_चिन्हित_info *sinfo)
अणु
	पूर्णांक ret;

	kenter(",%u", sinfo->index);

	/* First of all, digest the data in the PKCS#7 message and the
	 * चिन्हित inक्रमmation block
	 */
	ret = pkcs7_digest(pkcs7, sinfo);
	अगर (ret < 0)
		वापस ret;

	/* Find the key क्रम the signature अगर there is one */
	ret = pkcs7_find_key(pkcs7, sinfo);
	अगर (ret < 0)
		वापस ret;

	अगर (!sinfo->signer)
		वापस 0;

	pr_devel("Using X.509[%u] for sig %u\n",
		 sinfo->signer->index, sinfo->index);

	/* Check that the PKCS#7 signing समय is valid according to the X.509
	 * certअगरicate.  We can't, however, check against the प्रणाली घड़ी
	 * since that may not have been set yet and may be wrong.
	 */
	अगर (test_bit(sinfo_has_signing_समय, &sinfo->aa_set)) अणु
		अगर (sinfo->signing_समय < sinfo->signer->valid_from ||
		    sinfo->signing_समय > sinfo->signer->valid_to) अणु
			pr_warn("Message signed outside of X.509 validity window\n");
			वापस -EKEYREJECTED;
		पूर्ण
	पूर्ण

	/* Verअगरy the PKCS#7 binary against the key */
	ret = खुला_key_verअगरy_signature(sinfo->signer->pub, sinfo->sig);
	अगर (ret < 0)
		वापस ret;

	pr_devel("Verified signature %u\n", sinfo->index);

	/* Verअगरy the पूर्णांकernal certअगरicate chain */
	वापस pkcs7_verअगरy_sig_chain(pkcs7, sinfo);
पूर्ण

/**
 * pkcs7_verअगरy - Verअगरy a PKCS#7 message
 * @pkcs7: The PKCS#7 message to be verअगरied
 * @usage: The use to which the key is being put
 *
 * Verअगरy a PKCS#7 message is पूर्णांकernally consistent - that is, the data digest
 * matches the digest in the AuthAttrs and any signature in the message or one
 * of the X.509 certअगरicates it carries that matches another X.509 cert in the
 * message can be verअगरied.
 *
 * This करोes not look to match the contents of the PKCS#7 message against any
 * बाह्यal खुला keys.
 *
 * Returns, in order of descending priority:
 *
 *  (*) -EKEYREJECTED अगर a key was selected that had a usage restriction at
 *      odds with the specअगरied usage, or:
 *
 *  (*) -EKEYREJECTED अगर a signature failed to match क्रम which we found an
 *	appropriate X.509 certअगरicate, or:
 *
 *  (*) -EBADMSG अगर some part of the message was invalid, or:
 *
 *  (*) 0 अगर a signature chain passed verअगरication, or:
 *
 *  (*) -EKEYREJECTED अगर a blacklisted key was encountered, or:
 *
 *  (*) -ENOPKG अगर none of the signature chains are verअगरiable because suitable
 *	crypto modules couldn't be found.
 */
पूर्णांक pkcs7_verअगरy(काष्ठा pkcs7_message *pkcs7,
		 क्रमागत key_being_used_क्रम usage)
अणु
	काष्ठा pkcs7_चिन्हित_info *sinfo;
	पूर्णांक actual_ret = -ENOPKG;
	पूर्णांक ret;

	kenter("");

	चयन (usage) अणु
	हाल VERIFYING_MODULE_SIGNATURE:
		अगर (pkcs7->data_type != OID_data) अणु
			pr_warn("Invalid module sig (not pkcs7-data)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		अगर (pkcs7->have_authattrs) अणु
			pr_warn("Invalid module sig (has authattrs)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		अवरोध;
	हाल VERIFYING_FIRMWARE_SIGNATURE:
		अगर (pkcs7->data_type != OID_data) अणु
			pr_warn("Invalid firmware sig (not pkcs7-data)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		अगर (!pkcs7->have_authattrs) अणु
			pr_warn("Invalid firmware sig (missing authattrs)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		अवरोध;
	हाल VERIFYING_KEXEC_PE_SIGNATURE:
		अगर (pkcs7->data_type != OID_msIndirectData) अणु
			pr_warn("Invalid kexec sig (not Authenticode)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		/* Authattr presence checked in parser */
		अवरोध;
	हाल VERIFYING_UNSPECIFIED_SIGNATURE:
		अगर (pkcs7->data_type != OID_data) अणु
			pr_warn("Invalid unspecified sig (not pkcs7-data)\n");
			वापस -EKEYREJECTED;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (sinfo = pkcs7->चिन्हित_infos; sinfo; sinfo = sinfo->next) अणु
		ret = pkcs7_verअगरy_one(pkcs7, sinfo);
		अगर (sinfo->blacklisted) अणु
			अगर (actual_ret == -ENOPKG)
				actual_ret = -EKEYREJECTED;
			जारी;
		पूर्ण
		अगर (ret < 0) अणु
			अगर (ret == -ENOPKG) अणु
				sinfo->unsupported_crypto = true;
				जारी;
			पूर्ण
			kleave(" = %d", ret);
			वापस ret;
		पूर्ण
		actual_ret = 0;
	पूर्ण

	kleave(" = %d", actual_ret);
	वापस actual_ret;
पूर्ण
EXPORT_SYMBOL_GPL(pkcs7_verअगरy);

/**
 * pkcs7_supply_detached_data - Supply the data needed to verअगरy a PKCS#7 message
 * @pkcs7: The PKCS#7 message
 * @data: The data to be verअगरied
 * @datalen: The amount of data
 *
 * Supply the detached data needed to verअगरy a PKCS#7 message.  Note that no
 * attempt to retain/pin the data is made.  That is left to the caller.  The
 * data will not be modअगरied by pkcs7_verअगरy() and will not be मुक्तd when the
 * PKCS#7 message is मुक्तd.
 *
 * Returns -EINVAL अगर data is alपढ़ोy supplied in the message, 0 otherwise.
 */
पूर्णांक pkcs7_supply_detached_data(काष्ठा pkcs7_message *pkcs7,
			       स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	अगर (pkcs7->data) अणु
		pr_debug("Data already supplied\n");
		वापस -EINVAL;
	पूर्ण
	pkcs7->data = data;
	pkcs7->data_len = datalen;
	वापस 0;
पूर्ण
