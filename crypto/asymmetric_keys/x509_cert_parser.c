<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* X.509 certअगरicate parser
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "X.509: "fmt
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/oid_registry.h>
#समावेश <crypto/खुला_key.h>
#समावेश "x509_parser.h"
#समावेश "x509.asn1.h"
#समावेश "x509_akid.asn1.h"

काष्ठा x509_parse_context अणु
	काष्ठा x509_certअगरicate	*cert;		/* Certअगरicate being स्थिरructed */
	अचिन्हित दीर्घ	data;			/* Start of data */
	स्थिर व्योम	*cert_start;		/* Start of cert content */
	स्थिर व्योम	*key;			/* Key data */
	माप_प्रकार		key_size;		/* Size of key data */
	स्थिर व्योम	*params;		/* Key parameters */
	माप_प्रकार		params_size;		/* Size of key parameters */
	क्रमागत OID	key_algo;		/* Public key algorithm */
	क्रमागत OID	last_oid;		/* Last OID encountered */
	क्रमागत OID	algo_oid;		/* Algorithm OID */
	अचिन्हित अक्षर	nr_mpi;			/* Number of MPIs stored */
	u8		o_size;			/* Size of organizationName (O) */
	u8		cn_size;		/* Size of commonName (CN) */
	u8		email_size;		/* Size of emailAddress */
	u16		o_offset;		/* Offset of organizationName (O) */
	u16		cn_offset;		/* Offset of commonName (CN) */
	u16		email_offset;		/* Offset of emailAddress */
	अचिन्हित	raw_akid_size;
	स्थिर व्योम	*raw_akid;		/* Raw authorityKeyId in ASN.1 */
	स्थिर व्योम	*akid_raw_issuer;	/* Raw directoryName in authorityKeyId */
	अचिन्हित	akid_raw_issuer_size;
पूर्ण;

/*
 * Free an X.509 certअगरicate
 */
व्योम x509_मुक्त_certअगरicate(काष्ठा x509_certअगरicate *cert)
अणु
	अगर (cert) अणु
		खुला_key_मुक्त(cert->pub);
		खुला_key_signature_मुक्त(cert->sig);
		kमुक्त(cert->issuer);
		kमुक्त(cert->subject);
		kमुक्त(cert->id);
		kमुक्त(cert->skid);
		kमुक्त(cert);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(x509_मुक्त_certअगरicate);

/*
 * Parse an X.509 certअगरicate
 */
काष्ठा x509_certअगरicate *x509_cert_parse(स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा x509_certअगरicate *cert;
	काष्ठा x509_parse_context *ctx;
	काष्ठा asymmetric_key_id *kid;
	दीर्घ ret;

	ret = -ENOMEM;
	cert = kzalloc(माप(काष्ठा x509_certअगरicate), GFP_KERNEL);
	अगर (!cert)
		जाओ error_no_cert;
	cert->pub = kzalloc(माप(काष्ठा खुला_key), GFP_KERNEL);
	अगर (!cert->pub)
		जाओ error_no_ctx;
	cert->sig = kzalloc(माप(काष्ठा खुला_key_signature), GFP_KERNEL);
	अगर (!cert->sig)
		जाओ error_no_ctx;
	ctx = kzalloc(माप(काष्ठा x509_parse_context), GFP_KERNEL);
	अगर (!ctx)
		जाओ error_no_ctx;

	ctx->cert = cert;
	ctx->data = (अचिन्हित दीर्घ)data;

	/* Attempt to decode the certअगरicate */
	ret = asn1_ber_decoder(&x509_decoder, ctx, data, datalen);
	अगर (ret < 0)
		जाओ error_decode;

	/* Decode the AuthorityKeyIdentअगरier */
	अगर (ctx->raw_akid) अणु
		pr_devel("AKID: %u %*phN\n",
			 ctx->raw_akid_size, ctx->raw_akid_size, ctx->raw_akid);
		ret = asn1_ber_decoder(&x509_akid_decoder, ctx,
				       ctx->raw_akid, ctx->raw_akid_size);
		अगर (ret < 0) अणु
			pr_warn("Couldn't decode AuthKeyIdentifier\n");
			जाओ error_decode;
		पूर्ण
	पूर्ण

	ret = -ENOMEM;
	cert->pub->key = kmemdup(ctx->key, ctx->key_size, GFP_KERNEL);
	अगर (!cert->pub->key)
		जाओ error_decode;

	cert->pub->keylen = ctx->key_size;

	cert->pub->params = kmemdup(ctx->params, ctx->params_size, GFP_KERNEL);
	अगर (!cert->pub->params)
		जाओ error_decode;

	cert->pub->paramlen = ctx->params_size;
	cert->pub->algo = ctx->key_algo;

	/* Grab the signature bits */
	ret = x509_get_sig_params(cert);
	अगर (ret < 0)
		जाओ error_decode;

	/* Generate cert issuer + serial number key ID */
	kid = asymmetric_key_generate_id(cert->raw_serial,
					 cert->raw_serial_size,
					 cert->raw_issuer,
					 cert->raw_issuer_size);
	अगर (IS_ERR(kid)) अणु
		ret = PTR_ERR(kid);
		जाओ error_decode;
	पूर्ण
	cert->id = kid;

	/* Detect self-चिन्हित certअगरicates */
	ret = x509_check_क्रम_self_चिन्हित(cert);
	अगर (ret < 0)
		जाओ error_decode;

	kमुक्त(ctx);
	वापस cert;

error_decode:
	kमुक्त(ctx);
error_no_ctx:
	x509_मुक्त_certअगरicate(cert);
error_no_cert:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(x509_cert_parse);

/*
 * Note an OID when we find one क्रम later processing when we know how
 * to पूर्णांकerpret it.
 */
पूर्णांक x509_note_OID(व्योम *context, माप_प्रकार hdrlen,
	     अचिन्हित अक्षर tag,
	     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	ctx->last_oid = look_up_OID(value, vlen);
	अगर (ctx->last_oid == OID__NR) अणु
		अक्षर buffer[50];
		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		pr_debug("Unknown OID: [%lu] %s\n",
			 (अचिन्हित दीर्घ)value - ctx->data, buffer);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Save the position of the TBS data so that we can check the signature over it
 * later.
 */
पूर्णांक x509_note_tbs_certअगरicate(व्योम *context, माप_प्रकार hdrlen,
			      अचिन्हित अक्षर tag,
			      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	pr_debug("x509_note_tbs_certificate(,%zu,%02x,%ld,%zu)!\n",
		 hdrlen, tag, (अचिन्हित दीर्घ)value - ctx->data, vlen);

	ctx->cert->tbs = value - hdrlen;
	ctx->cert->tbs_size = vlen + hdrlen;
	वापस 0;
पूर्ण

/*
 * Record the खुला key algorithm
 */
पूर्णांक x509_note_pkey_algo(व्योम *context, माप_प्रकार hdrlen,
			अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	pr_debug("PubKey Algo: %u\n", ctx->last_oid);

	चयन (ctx->last_oid) अणु
	हाल OID_md2WithRSAEncryption:
	हाल OID_md3WithRSAEncryption:
	शेष:
		वापस -ENOPKG; /* Unsupported combination */

	हाल OID_md4WithRSAEncryption:
		ctx->cert->sig->hash_algo = "md4";
		जाओ rsa_pkcs1;

	हाल OID_sha1WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha1";
		जाओ rsa_pkcs1;

	हाल OID_sha256WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha256";
		जाओ rsa_pkcs1;

	हाल OID_sha384WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha384";
		जाओ rsa_pkcs1;

	हाल OID_sha512WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha512";
		जाओ rsa_pkcs1;

	हाल OID_sha224WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha224";
		जाओ rsa_pkcs1;

	हाल OID_id_ecdsa_with_sha1:
		ctx->cert->sig->hash_algo = "sha1";
		जाओ ecdsa;

	हाल OID_id_ecdsa_with_sha224:
		ctx->cert->sig->hash_algo = "sha224";
		जाओ ecdsa;

	हाल OID_id_ecdsa_with_sha256:
		ctx->cert->sig->hash_algo = "sha256";
		जाओ ecdsa;

	हाल OID_id_ecdsa_with_sha384:
		ctx->cert->sig->hash_algo = "sha384";
		जाओ ecdsa;

	हाल OID_id_ecdsa_with_sha512:
		ctx->cert->sig->hash_algo = "sha512";
		जाओ ecdsa;

	हाल OID_gost2012Signature256:
		ctx->cert->sig->hash_algo = "streebog256";
		जाओ ecrdsa;

	हाल OID_gost2012Signature512:
		ctx->cert->sig->hash_algo = "streebog512";
		जाओ ecrdsa;

	हाल OID_SM2_with_SM3:
		ctx->cert->sig->hash_algo = "sm3";
		जाओ sm2;
	पूर्ण

rsa_pkcs1:
	ctx->cert->sig->pkey_algo = "rsa";
	ctx->cert->sig->encoding = "pkcs1";
	ctx->algo_oid = ctx->last_oid;
	वापस 0;
ecrdsa:
	ctx->cert->sig->pkey_algo = "ecrdsa";
	ctx->cert->sig->encoding = "raw";
	ctx->algo_oid = ctx->last_oid;
	वापस 0;
sm2:
	ctx->cert->sig->pkey_algo = "sm2";
	ctx->cert->sig->encoding = "raw";
	ctx->algo_oid = ctx->last_oid;
	वापस 0;
ecdsa:
	ctx->cert->sig->pkey_algo = "ecdsa";
	ctx->cert->sig->encoding = "x962";
	ctx->algo_oid = ctx->last_oid;
	वापस 0;
पूर्ण

/*
 * Note the whereabouts and type of the signature.
 */
पूर्णांक x509_note_signature(व्योम *context, माप_प्रकार hdrlen,
			अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	pr_debug("Signature type: %u size %zu\n", ctx->last_oid, vlen);

	अगर (ctx->last_oid != ctx->algo_oid) अणु
		pr_warn("Got cert with pkey (%u) and sig (%u) algorithm OIDs\n",
			ctx->algo_oid, ctx->last_oid);
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद(ctx->cert->sig->pkey_algo, "rsa") == 0 ||
	    म_भेद(ctx->cert->sig->pkey_algo, "ecrdsa") == 0 ||
	    म_भेद(ctx->cert->sig->pkey_algo, "sm2") == 0 ||
	    म_भेद(ctx->cert->sig->pkey_algo, "ecdsa") == 0) अणु
		/* Discard the BIT STRING metadata */
		अगर (vlen < 1 || *(स्थिर u8 *)value != 0)
			वापस -EBADMSG;

		value++;
		vlen--;
	पूर्ण

	ctx->cert->raw_sig = value;
	ctx->cert->raw_sig_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note the certअगरicate serial number
 */
पूर्णांक x509_note_serial(व्योम *context, माप_प्रकार hdrlen,
		     अचिन्हित अक्षर tag,
		     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	ctx->cert->raw_serial = value;
	ctx->cert->raw_serial_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note some of the name segments from which we'll fabricate a name.
 */
पूर्णांक x509_extract_name_segment(व्योम *context, माप_प्रकार hdrlen,
			      अचिन्हित अक्षर tag,
			      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	चयन (ctx->last_oid) अणु
	हाल OID_commonName:
		ctx->cn_size = vlen;
		ctx->cn_offset = (अचिन्हित दीर्घ)value - ctx->data;
		अवरोध;
	हाल OID_organizationName:
		ctx->o_size = vlen;
		ctx->o_offset = (अचिन्हित दीर्घ)value - ctx->data;
		अवरोध;
	हाल OID_email_address:
		ctx->email_size = vlen;
		ctx->email_offset = (अचिन्हित दीर्घ)value - ctx->data;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Fabricate and save the issuer and subject names
 */
अटल पूर्णांक x509_fabricate_name(काष्ठा x509_parse_context *ctx, माप_प्रकार hdrlen,
			       अचिन्हित अक्षर tag,
			       अक्षर **_name, माप_प्रकार vlen)
अणु
	स्थिर व्योम *name, *data = (स्थिर व्योम *)ctx->data;
	माप_प्रकार namesize;
	अक्षर *buffer;

	अगर (*_name)
		वापस -EINVAL;

	/* Empty name string अगर no material */
	अगर (!ctx->cn_size && !ctx->o_size && !ctx->email_size) अणु
		buffer = kदो_स्मृति(1, GFP_KERNEL);
		अगर (!buffer)
			वापस -ENOMEM;
		buffer[0] = 0;
		जाओ करोne;
	पूर्ण

	अगर (ctx->cn_size && ctx->o_size) अणु
		/* Consider combining O and CN, but use only the CN अगर it is
		 * prefixed by the O, or a signअगरicant portion thereof.
		 */
		namesize = ctx->cn_size;
		name = data + ctx->cn_offset;
		अगर (ctx->cn_size >= ctx->o_size &&
		    स_भेद(data + ctx->cn_offset, data + ctx->o_offset,
			   ctx->o_size) == 0)
			जाओ single_component;
		अगर (ctx->cn_size >= 7 &&
		    ctx->o_size >= 7 &&
		    स_भेद(data + ctx->cn_offset, data + ctx->o_offset, 7) == 0)
			जाओ single_component;

		buffer = kदो_स्मृति(ctx->o_size + 2 + ctx->cn_size + 1,
				 GFP_KERNEL);
		अगर (!buffer)
			वापस -ENOMEM;

		स_नकल(buffer,
		       data + ctx->o_offset, ctx->o_size);
		buffer[ctx->o_size + 0] = ':';
		buffer[ctx->o_size + 1] = ' ';
		स_नकल(buffer + ctx->o_size + 2,
		       data + ctx->cn_offset, ctx->cn_size);
		buffer[ctx->o_size + 2 + ctx->cn_size] = 0;
		जाओ करोne;

	पूर्ण अन्यथा अगर (ctx->cn_size) अणु
		namesize = ctx->cn_size;
		name = data + ctx->cn_offset;
	पूर्ण अन्यथा अगर (ctx->o_size) अणु
		namesize = ctx->o_size;
		name = data + ctx->o_offset;
	पूर्ण अन्यथा अणु
		namesize = ctx->email_size;
		name = data + ctx->email_offset;
	पूर्ण

single_component:
	buffer = kदो_स्मृति(namesize + 1, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	स_नकल(buffer, name, namesize);
	buffer[namesize] = 0;

करोne:
	*_name = buffer;
	ctx->cn_size = 0;
	ctx->o_size = 0;
	ctx->email_size = 0;
	वापस 0;
पूर्ण

पूर्णांक x509_note_issuer(व्योम *context, माप_प्रकार hdrlen,
		     अचिन्हित अक्षर tag,
		     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	ctx->cert->raw_issuer = value;
	ctx->cert->raw_issuer_size = vlen;
	वापस x509_fabricate_name(ctx, hdrlen, tag, &ctx->cert->issuer, vlen);
पूर्ण

पूर्णांक x509_note_subject(व्योम *context, माप_प्रकार hdrlen,
		      अचिन्हित अक्षर tag,
		      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	ctx->cert->raw_subject = value;
	ctx->cert->raw_subject_size = vlen;
	वापस x509_fabricate_name(ctx, hdrlen, tag, &ctx->cert->subject, vlen);
पूर्ण

/*
 * Extract the parameters क्रम the खुला key
 */
पूर्णांक x509_note_params(व्योम *context, माप_प्रकार hdrlen,
		     अचिन्हित अक्षर tag,
		     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	/*
	 * AlgorithmIdentअगरier is used three बार in the x509, we should skip
	 * first and ignore third, using second one which is after subject and
	 * beक्रमe subjectPublicKey.
	 */
	अगर (!ctx->cert->raw_subject || ctx->key)
		वापस 0;
	ctx->params = value - hdrlen;
	ctx->params_size = vlen + hdrlen;
	वापस 0;
पूर्ण

/*
 * Extract the data क्रम the खुला key algorithm
 */
पूर्णांक x509_extract_key_data(व्योम *context, माप_प्रकार hdrlen,
			  अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	क्रमागत OID oid;

	ctx->key_algo = ctx->last_oid;
	चयन (ctx->last_oid) अणु
	हाल OID_rsaEncryption:
		ctx->cert->pub->pkey_algo = "rsa";
		अवरोध;
	हाल OID_gost2012PKey256:
	हाल OID_gost2012PKey512:
		ctx->cert->pub->pkey_algo = "ecrdsa";
		अवरोध;
	हाल OID_id_ecPublicKey:
		अगर (parse_OID(ctx->params, ctx->params_size, &oid) != 0)
			वापस -EBADMSG;

		चयन (oid) अणु
		हाल OID_sm2:
			ctx->cert->pub->pkey_algo = "sm2";
			अवरोध;
		हाल OID_id_prime192v1:
			ctx->cert->pub->pkey_algo = "ecdsa-nist-p192";
			अवरोध;
		हाल OID_id_prime256v1:
			ctx->cert->pub->pkey_algo = "ecdsa-nist-p256";
			अवरोध;
		हाल OID_id_ansip384r1:
			ctx->cert->pub->pkey_algo = "ecdsa-nist-p384";
			अवरोध;
		शेष:
			वापस -ENOPKG;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOPKG;
	पूर्ण

	/* Discard the BIT STRING metadata */
	अगर (vlen < 1 || *(स्थिर u8 *)value != 0)
		वापस -EBADMSG;
	ctx->key = value + 1;
	ctx->key_size = vlen - 1;
	वापस 0;
पूर्ण

/* The keyIdentअगरier in AuthorityKeyIdentअगरier SEQUENCE is tag(CONT,PRIM,0) */
#घोषणा SEQ_TAG_KEYID (ASN1_CONT << 6)

/*
 * Process certअगरicate extensions that are used to qualअगरy the certअगरicate.
 */
पूर्णांक x509_process_extension(व्योम *context, माप_प्रकार hdrlen,
			   अचिन्हित अक्षर tag,
			   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	काष्ठा asymmetric_key_id *kid;
	स्थिर अचिन्हित अक्षर *v = value;

	pr_debug("Extension: %u\n", ctx->last_oid);

	अगर (ctx->last_oid == OID_subjectKeyIdentअगरier) अणु
		/* Get hold of the key fingerprपूर्णांक */
		अगर (ctx->cert->skid || vlen < 3)
			वापस -EBADMSG;
		अगर (v[0] != ASN1_OTS || v[1] != vlen - 2)
			वापस -EBADMSG;
		v += 2;
		vlen -= 2;

		ctx->cert->raw_skid_size = vlen;
		ctx->cert->raw_skid = v;
		kid = asymmetric_key_generate_id(v, vlen, "", 0);
		अगर (IS_ERR(kid))
			वापस PTR_ERR(kid);
		ctx->cert->skid = kid;
		pr_debug("subjkeyid %*phN\n", kid->len, kid->data);
		वापस 0;
	पूर्ण

	अगर (ctx->last_oid == OID_authorityKeyIdentअगरier) अणु
		/* Get hold of the CA key fingerprपूर्णांक */
		ctx->raw_akid = v;
		ctx->raw_akid_size = vlen;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * x509_decode_समय - Decode an X.509 समय ASN.1 object
 * @_t: The समय to fill in
 * @hdrlen: The length of the object header
 * @tag: The object tag
 * @value: The object value
 * @vlen: The size of the object value
 *
 * Decode an ASN.1 universal समय or generalised समय field पूर्णांकo a काष्ठा the
 * kernel can handle and check it क्रम validity.  The समय is decoded thus:
 *
 *	[RFC5280 तई4.1.2.5]
 *	CAs conक्रमming to this profile MUST always encode certअगरicate validity
 *	dates through the year 2049 as UTCTime; certअगरicate validity dates in
 *	2050 or later MUST be encoded as GeneralizedTime.  Conक्रमming
 *	applications MUST be able to process validity dates that are encoded in
 *	either UTCTime or GeneralizedTime.
 */
पूर्णांक x509_decode_समय(समय64_t *_t,  माप_प्रकार hdrlen,
		     अचिन्हित अक्षर tag,
		     स्थिर अचिन्हित अक्षर *value, माप_प्रकार vlen)
अणु
	अटल स्थिर अचिन्हित अक्षर month_lengths[] = अणु 31, 28, 31, 30, 31, 30,
						       31, 31, 30, 31, 30, 31 पूर्ण;
	स्थिर अचिन्हित अक्षर *p = value;
	अचिन्हित year, mon, day, hour, min, sec, mon_len;

#घोषणा dec2bin(X) (अणु अचिन्हित अक्षर x = (X) - '0'; अगर (x > 9) जाओ invalid_समय; x; पूर्ण)
#घोषणा DD2bin(P) (अणु अचिन्हित x = dec2bin(P[0]) * 10 + dec2bin(P[1]); P += 2; x; पूर्ण)

	अगर (tag == ASN1_UNITIM) अणु
		/* UTCTime: YYMMDDHHMMSSZ */
		अगर (vlen != 13)
			जाओ unsupported_समय;
		year = DD2bin(p);
		अगर (year >= 50)
			year += 1900;
		अन्यथा
			year += 2000;
	पूर्ण अन्यथा अगर (tag == ASN1_GENTIM) अणु
		/* GenTime: YYYYMMDDHHMMSSZ */
		अगर (vlen != 15)
			जाओ unsupported_समय;
		year = DD2bin(p) * 100 + DD2bin(p);
		अगर (year >= 1950 && year <= 2049)
			जाओ invalid_समय;
	पूर्ण अन्यथा अणु
		जाओ unsupported_समय;
	पूर्ण

	mon  = DD2bin(p);
	day = DD2bin(p);
	hour = DD2bin(p);
	min  = DD2bin(p);
	sec  = DD2bin(p);

	अगर (*p != 'Z')
		जाओ unsupported_समय;

	अगर (year < 1970 ||
	    mon < 1 || mon > 12)
		जाओ invalid_समय;

	mon_len = month_lengths[mon - 1];
	अगर (mon == 2) अणु
		अगर (year % 4 == 0) अणु
			mon_len = 29;
			अगर (year % 100 == 0) अणु
				mon_len = 28;
				अगर (year % 400 == 0)
					mon_len = 29;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (day < 1 || day > mon_len ||
	    hour > 24 || /* ISO 8601 permits 24:00:00 as midnight tomorrow */
	    min > 59 ||
	    sec > 60) /* ISO 8601 permits leap seconds [X.680 46.3] */
		जाओ invalid_समय;

	*_t = स_गढ़ो64(year, mon, day, hour, min, sec);
	वापस 0;

unsupported_समय:
	pr_debug("Got unsupported time [tag %02x]: '%*phN'\n",
		 tag, (पूर्णांक)vlen, value);
	वापस -EBADMSG;
invalid_समय:
	pr_debug("Got invalid time [tag %02x]: '%*phN'\n",
		 tag, (पूर्णांक)vlen, value);
	वापस -EBADMSG;
पूर्ण
EXPORT_SYMBOL_GPL(x509_decode_समय);

पूर्णांक x509_note_not_beक्रमe(व्योम *context, माप_प्रकार hdrlen,
			 अचिन्हित अक्षर tag,
			 स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	वापस x509_decode_समय(&ctx->cert->valid_from, hdrlen, tag, value, vlen);
पूर्ण

पूर्णांक x509_note_not_after(व्योम *context, माप_प्रकार hdrlen,
			अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	वापस x509_decode_समय(&ctx->cert->valid_to, hdrlen, tag, value, vlen);
पूर्ण

/*
 * Note a key identअगरier-based AuthorityKeyIdentअगरier
 */
पूर्णांक x509_akid_note_kid(व्योम *context, माप_प्रकार hdrlen,
		       अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	काष्ठा asymmetric_key_id *kid;

	pr_debug("AKID: keyid: %*phN\n", (पूर्णांक)vlen, value);

	अगर (ctx->cert->sig->auth_ids[1])
		वापस 0;

	kid = asymmetric_key_generate_id(value, vlen, "", 0);
	अगर (IS_ERR(kid))
		वापस PTR_ERR(kid);
	pr_debug("authkeyid %*phN\n", kid->len, kid->data);
	ctx->cert->sig->auth_ids[1] = kid;
	वापस 0;
पूर्ण

/*
 * Note a directoryName in an AuthorityKeyIdentअगरier
 */
पूर्णांक x509_akid_note_name(व्योम *context, माप_प्रकार hdrlen,
			अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;

	pr_debug("AKID: name: %*phN\n", (पूर्णांक)vlen, value);

	ctx->akid_raw_issuer = value;
	ctx->akid_raw_issuer_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note a serial number in an AuthorityKeyIdentअगरier
 */
पूर्णांक x509_akid_note_serial(व्योम *context, माप_प्रकार hdrlen,
			  अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा x509_parse_context *ctx = context;
	काष्ठा asymmetric_key_id *kid;

	pr_debug("AKID: serial: %*phN\n", (पूर्णांक)vlen, value);

	अगर (!ctx->akid_raw_issuer || ctx->cert->sig->auth_ids[0])
		वापस 0;

	kid = asymmetric_key_generate_id(value,
					 vlen,
					 ctx->akid_raw_issuer,
					 ctx->akid_raw_issuer_size);
	अगर (IS_ERR(kid))
		वापस PTR_ERR(kid);

	pr_debug("authkeyid %*phN\n", kid->len, kid->data);
	ctx->cert->sig->auth_ids[0] = kid;
	वापस 0;
पूर्ण
