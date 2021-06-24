<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Parse a Microsoft Inभागidual Code Signing blob
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "MSCODE: "fmt
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/oid_registry.h>
#समावेश <crypto/pkcs7.h>
#समावेश "verify_pefile.h"
#समावेश "mscode.asn1.h"

/*
 * Parse a Microsoft Inभागidual Code Signing blob
 */
पूर्णांक mscode_parse(व्योम *_ctx, स्थिर व्योम *content_data, माप_प्रकार data_len,
		 माप_प्रकार asn1hdrlen)
अणु
	काष्ठा pefile_context *ctx = _ctx;

	content_data -= asn1hdrlen;
	data_len += asn1hdrlen;
	pr_devel("Data: %zu [%*ph]\n", data_len, (अचिन्हित)(data_len),
		 content_data);

	वापस asn1_ber_decoder(&mscode_decoder, ctx, content_data, data_len);
पूर्ण

/*
 * Check the content type OID
 */
पूर्णांक mscode_note_content_type(व्योम *context, माप_प्रकार hdrlen,
			     अचिन्हित अक्षर tag,
			     स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	क्रमागत OID oid;

	oid = look_up_OID(value, vlen);
	अगर (oid == OID__NR) अणु
		अक्षर buffer[50];

		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		pr_err("Unknown OID: %s\n", buffer);
		वापस -EBADMSG;
	पूर्ण

	/*
	 * pesign utility had a bug where it was putting
	 * OID_msInभागidualSPKeyPurpose instead of OID_msPeImageDataObjId
	 * So allow both OIDs.
	 */
	अगर (oid != OID_msPeImageDataObjId &&
	    oid != OID_msInभागidualSPKeyPurpose) अणु
		pr_err("Unexpected content type OID %u\n", oid);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note the digest algorithm OID
 */
पूर्णांक mscode_note_digest_algo(व्योम *context, माप_प्रकार hdrlen,
			    अचिन्हित अक्षर tag,
			    स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pefile_context *ctx = context;
	अक्षर buffer[50];
	क्रमागत OID oid;

	oid = look_up_OID(value, vlen);
	चयन (oid) अणु
	हाल OID_md4:
		ctx->digest_algo = "md4";
		अवरोध;
	हाल OID_md5:
		ctx->digest_algo = "md5";
		अवरोध;
	हाल OID_sha1:
		ctx->digest_algo = "sha1";
		अवरोध;
	हाल OID_sha256:
		ctx->digest_algo = "sha256";
		अवरोध;
	हाल OID_sha384:
		ctx->digest_algo = "sha384";
		अवरोध;
	हाल OID_sha512:
		ctx->digest_algo = "sha512";
		अवरोध;
	हाल OID_sha224:
		ctx->digest_algo = "sha224";
		अवरोध;

	हाल OID__NR:
		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		pr_err("Unknown OID: %s\n", buffer);
		वापस -EBADMSG;

	शेष:
		pr_err("Unsupported content type: %u\n", oid);
		वापस -ENOPKG;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note the digest we're guaranteeing with this certअगरicate
 */
पूर्णांक mscode_note_digest(व्योम *context, माप_प्रकार hdrlen,
		       अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pefile_context *ctx = context;

	ctx->digest = kmemdup(value, vlen, GFP_KERNEL);
	अगर (!ctx->digest)
		वापस -ENOMEM;

	ctx->digest_len = vlen;

	वापस 0;
पूर्ण
