<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* PKCS#7 parser
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PKCS7: "fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/oid_registry.h>
#समावेश <crypto/खुला_key.h>
#समावेश "pkcs7_parser.h"
#समावेश "pkcs7.asn1.h"

MODULE_DESCRIPTION("PKCS#7 parser");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

काष्ठा pkcs7_parse_context अणु
	काष्ठा pkcs7_message	*msg;		/* Message being स्थिरructed */
	काष्ठा pkcs7_चिन्हित_info *sinfo;	/* SignedInfo being स्थिरructed */
	काष्ठा pkcs7_चिन्हित_info **ppsinfo;
	काष्ठा x509_certअगरicate *certs;		/* Certअगरicate cache */
	काष्ठा x509_certअगरicate **ppcerts;
	अचिन्हित दीर्घ	data;			/* Start of data */
	क्रमागत OID	last_oid;		/* Last OID encountered */
	अचिन्हित	x509_index;
	अचिन्हित	sinfo_index;
	स्थिर व्योम	*raw_serial;
	अचिन्हित	raw_serial_size;
	अचिन्हित	raw_issuer_size;
	स्थिर व्योम	*raw_issuer;
	स्थिर व्योम	*raw_skid;
	अचिन्हित	raw_skid_size;
	bool		expect_skid;
पूर्ण;

/*
 * Free a चिन्हित inक्रमmation block.
 */
अटल व्योम pkcs7_मुक्त_चिन्हित_info(काष्ठा pkcs7_चिन्हित_info *sinfo)
अणु
	अगर (sinfo) अणु
		खुला_key_signature_मुक्त(sinfo->sig);
		kमुक्त(sinfo);
	पूर्ण
पूर्ण

/**
 * pkcs7_मुक्त_message - Free a PKCS#7 message
 * @pkcs7: The PKCS#7 message to मुक्त
 */
व्योम pkcs7_मुक्त_message(काष्ठा pkcs7_message *pkcs7)
अणु
	काष्ठा x509_certअगरicate *cert;
	काष्ठा pkcs7_चिन्हित_info *sinfo;

	अगर (pkcs7) अणु
		जबतक (pkcs7->certs) अणु
			cert = pkcs7->certs;
			pkcs7->certs = cert->next;
			x509_मुक्त_certअगरicate(cert);
		पूर्ण
		जबतक (pkcs7->crl) अणु
			cert = pkcs7->crl;
			pkcs7->crl = cert->next;
			x509_मुक्त_certअगरicate(cert);
		पूर्ण
		जबतक (pkcs7->चिन्हित_infos) अणु
			sinfo = pkcs7->चिन्हित_infos;
			pkcs7->चिन्हित_infos = sinfo->next;
			pkcs7_मुक्त_चिन्हित_info(sinfo);
		पूर्ण
		kमुक्त(pkcs7);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pkcs7_मुक्त_message);

/*
 * Check authenticatedAttributes are provided or not provided consistently.
 */
अटल पूर्णांक pkcs7_check_authattrs(काष्ठा pkcs7_message *msg)
अणु
	काष्ठा pkcs7_चिन्हित_info *sinfo;
	bool want = false;

	sinfo = msg->चिन्हित_infos;
	अगर (!sinfo)
		जाओ inconsistent;

	अगर (sinfo->authattrs) अणु
		want = true;
		msg->have_authattrs = true;
	पूर्ण

	क्रम (sinfo = sinfo->next; sinfo; sinfo = sinfo->next)
		अगर (!!sinfo->authattrs != want)
			जाओ inconsistent;
	वापस 0;

inconsistent:
	pr_warn("Inconsistently supplied authAttrs\n");
	वापस -EINVAL;
पूर्ण

/**
 * pkcs7_parse_message - Parse a PKCS#7 message
 * @data: The raw binary ASN.1 encoded message to be parsed
 * @datalen: The size of the encoded message
 */
काष्ठा pkcs7_message *pkcs7_parse_message(स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा pkcs7_parse_context *ctx;
	काष्ठा pkcs7_message *msg = ERR_PTR(-ENOMEM);
	पूर्णांक ret;

	ctx = kzalloc(माप(काष्ठा pkcs7_parse_context), GFP_KERNEL);
	अगर (!ctx)
		जाओ out_no_ctx;
	ctx->msg = kzalloc(माप(काष्ठा pkcs7_message), GFP_KERNEL);
	अगर (!ctx->msg)
		जाओ out_no_msg;
	ctx->sinfo = kzalloc(माप(काष्ठा pkcs7_चिन्हित_info), GFP_KERNEL);
	अगर (!ctx->sinfo)
		जाओ out_no_sinfo;
	ctx->sinfo->sig = kzalloc(माप(काष्ठा खुला_key_signature),
				  GFP_KERNEL);
	अगर (!ctx->sinfo->sig)
		जाओ out_no_sig;

	ctx->data = (अचिन्हित दीर्घ)data;
	ctx->ppcerts = &ctx->certs;
	ctx->ppsinfo = &ctx->msg->चिन्हित_infos;

	/* Attempt to decode the signature */
	ret = asn1_ber_decoder(&pkcs7_decoder, ctx, data, datalen);
	अगर (ret < 0) अणु
		msg = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	ret = pkcs7_check_authattrs(ctx->msg);
	अगर (ret < 0) अणु
		msg = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	msg = ctx->msg;
	ctx->msg = शून्य;

out:
	जबतक (ctx->certs) अणु
		काष्ठा x509_certअगरicate *cert = ctx->certs;
		ctx->certs = cert->next;
		x509_मुक्त_certअगरicate(cert);
	पूर्ण
out_no_sig:
	pkcs7_मुक्त_चिन्हित_info(ctx->sinfo);
out_no_sinfo:
	pkcs7_मुक्त_message(ctx->msg);
out_no_msg:
	kमुक्त(ctx);
out_no_ctx:
	वापस msg;
पूर्ण
EXPORT_SYMBOL_GPL(pkcs7_parse_message);

/**
 * pkcs7_get_content_data - Get access to the PKCS#7 content
 * @pkcs7: The preparsed PKCS#7 message to access
 * @_data: Place to वापस a poपूर्णांकer to the data
 * @_data_len: Place to वापस the data length
 * @_headerlen: Size of ASN.1 header not included in _data
 *
 * Get access to the data content of the PKCS#7 message.  The size of the
 * header of the ASN.1 object that contains it is also provided and can be used
 * to adjust *_data and *_data_len to get the entire object.
 *
 * Returns -ENODATA अगर the data object was missing from the message.
 */
पूर्णांक pkcs7_get_content_data(स्थिर काष्ठा pkcs7_message *pkcs7,
			   स्थिर व्योम **_data, माप_प्रकार *_data_len,
			   माप_प्रकार *_headerlen)
अणु
	अगर (!pkcs7->data)
		वापस -ENODATA;

	*_data = pkcs7->data;
	*_data_len = pkcs7->data_len;
	अगर (_headerlen)
		*_headerlen = pkcs7->data_hdrlen;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pkcs7_get_content_data);

/*
 * Note an OID when we find one क्रम later processing when we know how
 * to पूर्णांकerpret it.
 */
पूर्णांक pkcs7_note_OID(व्योम *context, माप_प्रकार hdrlen,
		   अचिन्हित अक्षर tag,
		   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	ctx->last_oid = look_up_OID(value, vlen);
	अगर (ctx->last_oid == OID__NR) अणु
		अक्षर buffer[50];
		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		prपूर्णांकk("PKCS7: Unknown OID: [%lu] %s\n",
		       (अचिन्हित दीर्घ)value - ctx->data, buffer);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note the digest algorithm क्रम the signature.
 */
पूर्णांक pkcs7_sig_note_digest_algo(व्योम *context, माप_प्रकार hdrlen,
			       अचिन्हित अक्षर tag,
			       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	चयन (ctx->last_oid) अणु
	हाल OID_md4:
		ctx->sinfo->sig->hash_algo = "md4";
		अवरोध;
	हाल OID_md5:
		ctx->sinfo->sig->hash_algo = "md5";
		अवरोध;
	हाल OID_sha1:
		ctx->sinfo->sig->hash_algo = "sha1";
		अवरोध;
	हाल OID_sha256:
		ctx->sinfo->sig->hash_algo = "sha256";
		अवरोध;
	हाल OID_sha384:
		ctx->sinfo->sig->hash_algo = "sha384";
		अवरोध;
	हाल OID_sha512:
		ctx->sinfo->sig->hash_algo = "sha512";
		अवरोध;
	हाल OID_sha224:
		ctx->sinfo->sig->hash_algo = "sha224";
		अवरोध;
	शेष:
		prपूर्णांकk("Unsupported digest algo: %u\n", ctx->last_oid);
		वापस -ENOPKG;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note the खुला key algorithm क्रम the signature.
 */
पूर्णांक pkcs7_sig_note_pkey_algo(व्योम *context, माप_प्रकार hdrlen,
			     अचिन्हित अक्षर tag,
			     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	चयन (ctx->last_oid) अणु
	हाल OID_rsaEncryption:
		ctx->sinfo->sig->pkey_algo = "rsa";
		ctx->sinfo->sig->encoding = "pkcs1";
		अवरोध;
	शेष:
		prपूर्णांकk("Unsupported pkey algo: %u\n", ctx->last_oid);
		वापस -ENOPKG;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * We only support चिन्हित data [RFC2315 sec 9].
 */
पूर्णांक pkcs7_check_content_type(व्योम *context, माप_प्रकार hdrlen,
			     अचिन्हित अक्षर tag,
			     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	अगर (ctx->last_oid != OID_चिन्हित_data) अणु
		pr_warn("Only support pkcs7_signedData type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note the SignedData version
 */
पूर्णांक pkcs7_note_चिन्हितdata_version(व्योम *context, माप_प्रकार hdrlen,
				  अचिन्हित अक्षर tag,
				  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	अचिन्हित version;

	अगर (vlen != 1)
		जाओ unsupported;

	ctx->msg->version = version = *(स्थिर u8 *)value;
	चयन (version) अणु
	हाल 1:
		/* PKCS#7 SignedData [RFC2315 sec 9.1]
		 * CMS ver 1 SignedData [RFC5652 sec 5.1]
		 */
		अवरोध;
	हाल 3:
		/* CMS ver 3 SignedData [RFC2315 sec 5.1] */
		अवरोध;
	शेष:
		जाओ unsupported;
	पूर्ण

	वापस 0;

unsupported:
	pr_warn("Unsupported SignedData version\n");
	वापस -EINVAL;
पूर्ण

/*
 * Note the SignerInfo version
 */
पूर्णांक pkcs7_note_signerinfo_version(व्योम *context, माप_प्रकार hdrlen,
				  अचिन्हित अक्षर tag,
				  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	अचिन्हित version;

	अगर (vlen != 1)
		जाओ unsupported;

	version = *(स्थिर u8 *)value;
	चयन (version) अणु
	हाल 1:
		/* PKCS#7 SignerInfo [RFC2315 sec 9.2]
		 * CMS ver 1 SignerInfo [RFC5652 sec 5.3]
		 */
		अगर (ctx->msg->version != 1)
			जाओ version_mismatch;
		ctx->expect_skid = false;
		अवरोध;
	हाल 3:
		/* CMS ver 3 SignerInfo [RFC2315 sec 5.3] */
		अगर (ctx->msg->version == 1)
			जाओ version_mismatch;
		ctx->expect_skid = true;
		अवरोध;
	शेष:
		जाओ unsupported;
	पूर्ण

	वापस 0;

unsupported:
	pr_warn("Unsupported SignerInfo version\n");
	वापस -EINVAL;
version_mismatch:
	pr_warn("SignedData-SignerInfo version mismatch\n");
	वापस -EBADMSG;
पूर्ण

/*
 * Extract a certअगरicate and store it in the context.
 */
पूर्णांक pkcs7_extract_cert(व्योम *context, माप_प्रकार hdrlen,
		       अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	काष्ठा x509_certअगरicate *x509;

	अगर (tag != ((ASN1_UNIV << 6) | ASN1_CONS_BIT | ASN1_SEQ)) अणु
		pr_debug("Cert began with tag %02x at %lu\n",
			 tag, (अचिन्हित दीर्घ)ctx - ctx->data);
		वापस -EBADMSG;
	पूर्ण

	/* We have to correct क्रम the header so that the X.509 parser can start
	 * from the beginning.  Note that since X.509 stipulates DER, there
	 * probably shouldn't be an EOC trailer - but it is in PKCS#7 (which
	 * stipulates BER).
	 */
	value -= hdrlen;
	vlen += hdrlen;

	अगर (((u8*)value)[1] == 0x80)
		vlen += 2; /* Indefinite length - there should be an EOC */

	x509 = x509_cert_parse(value, vlen);
	अगर (IS_ERR(x509))
		वापस PTR_ERR(x509);

	x509->index = ++ctx->x509_index;
	pr_debug("Got cert %u for %s\n", x509->index, x509->subject);
	pr_debug("- fingerprint %*phN\n", x509->id->len, x509->id->data);

	*ctx->ppcerts = x509;
	ctx->ppcerts = &x509->next;
	वापस 0;
पूर्ण

/*
 * Save the certअगरicate list
 */
पूर्णांक pkcs7_note_certअगरicate_list(व्योम *context, माप_प्रकार hdrlen,
				अचिन्हित अक्षर tag,
				स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	pr_devel("Got cert list (%02x)\n", tag);

	*ctx->ppcerts = ctx->msg->certs;
	ctx->msg->certs = ctx->certs;
	ctx->certs = शून्य;
	ctx->ppcerts = &ctx->certs;
	वापस 0;
पूर्ण

/*
 * Note the content type.
 */
पूर्णांक pkcs7_note_content(व्योम *context, माप_प्रकार hdrlen,
		       अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	अगर (ctx->last_oid != OID_data &&
	    ctx->last_oid != OID_msIndirectData) अणु
		pr_warn("Unsupported data type %d\n", ctx->last_oid);
		वापस -EINVAL;
	पूर्ण

	ctx->msg->data_type = ctx->last_oid;
	वापस 0;
पूर्ण

/*
 * Extract the data from the message and store that and its content type OID in
 * the context.
 */
पूर्णांक pkcs7_note_data(व्योम *context, माप_प्रकार hdrlen,
		    अचिन्हित अक्षर tag,
		    स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	pr_debug("Got data\n");

	ctx->msg->data = value;
	ctx->msg->data_len = vlen;
	ctx->msg->data_hdrlen = hdrlen;
	वापस 0;
पूर्ण

/*
 * Parse authenticated attributes.
 */
पूर्णांक pkcs7_sig_note_authenticated_attr(व्योम *context, माप_प्रकार hdrlen,
				      अचिन्हित अक्षर tag,
				      स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	काष्ठा pkcs7_चिन्हित_info *sinfo = ctx->sinfo;
	क्रमागत OID content_type;

	pr_devel("AuthAttr: %02x %zu [%*ph]\n", tag, vlen, (अचिन्हित)vlen, value);

	चयन (ctx->last_oid) अणु
	हाल OID_contentType:
		अगर (__test_and_set_bit(sinfo_has_content_type, &sinfo->aa_set))
			जाओ repeated;
		content_type = look_up_OID(value, vlen);
		अगर (content_type != ctx->msg->data_type) अणु
			pr_warn("Mismatch between global data type (%d) and sinfo %u (%d)\n",
				ctx->msg->data_type, sinfo->index,
				content_type);
			वापस -EBADMSG;
		पूर्ण
		वापस 0;

	हाल OID_signingTime:
		अगर (__test_and_set_bit(sinfo_has_signing_समय, &sinfo->aa_set))
			जाओ repeated;
		/* Should we check that the signing समय is consistent
		 * with the signer's X.509 cert?
		 */
		वापस x509_decode_समय(&sinfo->signing_समय,
					hdrlen, tag, value, vlen);

	हाल OID_messageDigest:
		अगर (__test_and_set_bit(sinfo_has_message_digest, &sinfo->aa_set))
			जाओ repeated;
		अगर (tag != ASN1_OTS)
			वापस -EBADMSG;
		sinfo->msgdigest = value;
		sinfo->msgdigest_len = vlen;
		वापस 0;

	हाल OID_smimeCapabilites:
		अगर (__test_and_set_bit(sinfo_has_smime_caps, &sinfo->aa_set))
			जाओ repeated;
		अगर (ctx->msg->data_type != OID_msIndirectData) अणु
			pr_warn("S/MIME Caps only allowed with Authenticode\n");
			वापस -EKEYREJECTED;
		पूर्ण
		वापस 0;

		/* Microsoft SpOpusInfo seems to be contain cont[0] 16-bit BE
		 * अक्षर URLs and cont[1] 8-bit अक्षर URLs.
		 *
		 * Microsoft StatementType seems to contain a list of OIDs that
		 * are also used as extendedKeyUsage types in X.509 certs.
		 */
	हाल OID_msSpOpusInfo:
		अगर (__test_and_set_bit(sinfo_has_ms_opus_info, &sinfo->aa_set))
			जाओ repeated;
		जाओ authenticode_check;
	हाल OID_msStatementType:
		अगर (__test_and_set_bit(sinfo_has_ms_statement_type, &sinfo->aa_set))
			जाओ repeated;
	authenticode_check:
		अगर (ctx->msg->data_type != OID_msIndirectData) अणु
			pr_warn("Authenticode AuthAttrs only allowed with Authenticode\n");
			वापस -EKEYREJECTED;
		पूर्ण
		/* I'm not sure how to validate these */
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण

repeated:
	/* We permit max one item per AuthenticatedAttribute and no repeats */
	pr_warn("Repeated/multivalue AuthAttrs not permitted\n");
	वापस -EKEYREJECTED;
पूर्ण

/*
 * Note the set of auth attributes क्रम digestion purposes [RFC2315 sec 9.3]
 */
पूर्णांक pkcs7_sig_note_set_of_authattrs(व्योम *context, माप_प्रकार hdrlen,
				    अचिन्हित अक्षर tag,
				    स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	काष्ठा pkcs7_चिन्हित_info *sinfo = ctx->sinfo;

	अगर (!test_bit(sinfo_has_content_type, &sinfo->aa_set) ||
	    !test_bit(sinfo_has_message_digest, &sinfo->aa_set)) अणु
		pr_warn("Missing required AuthAttr\n");
		वापस -EBADMSG;
	पूर्ण

	अगर (ctx->msg->data_type != OID_msIndirectData &&
	    test_bit(sinfo_has_ms_opus_info, &sinfo->aa_set)) अणु
		pr_warn("Unexpected Authenticode AuthAttr\n");
		वापस -EBADMSG;
	पूर्ण

	/* We need to चयन the 'CONT 0' to a 'SET OF' when we digest */
	sinfo->authattrs = value - (hdrlen - 1);
	sinfo->authattrs_len = vlen + (hdrlen - 1);
	वापस 0;
पूर्ण

/*
 * Note the issuing certअगरicate serial number
 */
पूर्णांक pkcs7_sig_note_serial(व्योम *context, माप_प्रकार hdrlen,
			  अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	ctx->raw_serial = value;
	ctx->raw_serial_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note the issuer's name
 */
पूर्णांक pkcs7_sig_note_issuer(व्योम *context, माप_प्रकार hdrlen,
			  अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	ctx->raw_issuer = value;
	ctx->raw_issuer_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note the issuing cert's subjectKeyIdentअगरier
 */
पूर्णांक pkcs7_sig_note_skid(व्योम *context, माप_प्रकार hdrlen,
			अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	pr_devel("SKID: %02x %zu [%*ph]\n", tag, vlen, (अचिन्हित)vlen, value);

	ctx->raw_skid = value;
	ctx->raw_skid_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note the signature data
 */
पूर्णांक pkcs7_sig_note_signature(व्योम *context, माप_प्रकार hdrlen,
			     अचिन्हित अक्षर tag,
			     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;

	ctx->sinfo->sig->s = kmemdup(value, vlen, GFP_KERNEL);
	अगर (!ctx->sinfo->sig->s)
		वापस -ENOMEM;

	ctx->sinfo->sig->s_size = vlen;
	वापस 0;
पूर्ण

/*
 * Note a signature inक्रमmation block
 */
पूर्णांक pkcs7_note_चिन्हित_info(व्योम *context, माप_प्रकार hdrlen,
			   अचिन्हित अक्षर tag,
			   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs7_parse_context *ctx = context;
	काष्ठा pkcs7_चिन्हित_info *sinfo = ctx->sinfo;
	काष्ठा asymmetric_key_id *kid;

	अगर (ctx->msg->data_type == OID_msIndirectData && !sinfo->authattrs) अणु
		pr_warn("Authenticode requires AuthAttrs\n");
		वापस -EBADMSG;
	पूर्ण

	/* Generate cert issuer + serial number key ID */
	अगर (!ctx->expect_skid) अणु
		kid = asymmetric_key_generate_id(ctx->raw_serial,
						 ctx->raw_serial_size,
						 ctx->raw_issuer,
						 ctx->raw_issuer_size);
	पूर्ण अन्यथा अणु
		kid = asymmetric_key_generate_id(ctx->raw_skid,
						 ctx->raw_skid_size,
						 "", 0);
	पूर्ण
	अगर (IS_ERR(kid))
		वापस PTR_ERR(kid);

	pr_devel("SINFO KID: %u [%*phN]\n", kid->len, kid->len, kid->data);

	sinfo->sig->auth_ids[0] = kid;
	sinfo->index = ++ctx->sinfo_index;
	*ctx->ppsinfo = sinfo;
	ctx->ppsinfo = &sinfo->next;
	ctx->sinfo = kzalloc(माप(काष्ठा pkcs7_चिन्हित_info), GFP_KERNEL);
	अगर (!ctx->sinfo)
		वापस -ENOMEM;
	ctx->sinfo->sig = kzalloc(माप(काष्ठा खुला_key_signature),
				  GFP_KERNEL);
	अगर (!ctx->sinfo->sig)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
