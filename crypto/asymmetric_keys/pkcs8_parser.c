<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* PKCS#8 Private Key parser [RFC 5208].
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PKCS8: "fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/oid_registry.h>
#समावेश <keys/asymmetric-subtype.h>
#समावेश <keys/asymmetric-parser.h>
#समावेश <crypto/खुला_key.h>
#समावेश "pkcs8.asn1.h"

काष्ठा pkcs8_parse_context अणु
	काष्ठा खुला_key *pub;
	अचिन्हित दीर्घ	data;			/* Start of data */
	क्रमागत OID	last_oid;		/* Last OID encountered */
	क्रमागत OID	algo_oid;		/* Algorithm OID */
	u32		key_size;
	स्थिर व्योम	*key;
पूर्ण;

/*
 * Note an OID when we find one क्रम later processing when we know how to
 * पूर्णांकerpret it.
 */
पूर्णांक pkcs8_note_OID(व्योम *context, माप_प्रकार hdrlen,
		   अचिन्हित अक्षर tag,
		   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs8_parse_context *ctx = context;

	ctx->last_oid = look_up_OID(value, vlen);
	अगर (ctx->last_oid == OID__NR) अणु
		अक्षर buffer[50];

		sprपूर्णांक_oid(value, vlen, buffer, माप(buffer));
		pr_info("Unknown OID: [%lu] %s\n",
			(अचिन्हित दीर्घ)value - ctx->data, buffer);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note the version number of the ASN.1 blob.
 */
पूर्णांक pkcs8_note_version(व्योम *context, माप_प्रकार hdrlen,
		       अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	अगर (vlen != 1 || ((स्थिर u8 *)value)[0] != 0) अणु
		pr_warn("Unsupported PKCS#8 version\n");
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note the खुला algorithm.
 */
पूर्णांक pkcs8_note_algo(व्योम *context, माप_प्रकार hdrlen,
		    अचिन्हित अक्षर tag,
		    स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs8_parse_context *ctx = context;

	अगर (ctx->last_oid != OID_rsaEncryption)
		वापस -ENOPKG;

	ctx->pub->pkey_algo = "rsa";
	वापस 0;
पूर्ण

/*
 * Note the key data of the ASN.1 blob.
 */
पूर्णांक pkcs8_note_key(व्योम *context, माप_प्रकार hdrlen,
		   अचिन्हित अक्षर tag,
		   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा pkcs8_parse_context *ctx = context;

	ctx->key = value;
	ctx->key_size = vlen;
	वापस 0;
पूर्ण

/*
 * Parse a PKCS#8 निजी key blob.
 */
अटल काष्ठा खुला_key *pkcs8_parse(स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा pkcs8_parse_context ctx;
	काष्ठा खुला_key *pub;
	दीर्घ ret;

	स_रखो(&ctx, 0, माप(ctx));

	ret = -ENOMEM;
	ctx.pub = kzalloc(माप(काष्ठा खुला_key), GFP_KERNEL);
	अगर (!ctx.pub)
		जाओ error;

	ctx.data = (अचिन्हित दीर्घ)data;

	/* Attempt to decode the निजी key */
	ret = asn1_ber_decoder(&pkcs8_decoder, &ctx, data, datalen);
	अगर (ret < 0)
		जाओ error_decode;

	ret = -ENOMEM;
	pub = ctx.pub;
	pub->key = kmemdup(ctx.key, ctx.key_size, GFP_KERNEL);
	अगर (!pub->key)
		जाओ error_decode;

	pub->keylen = ctx.key_size;
	pub->key_is_निजी = true;
	वापस pub;

error_decode:
	kमुक्त(ctx.pub);
error:
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Attempt to parse a data blob क्रम a key as a PKCS#8 निजी key.
 */
अटल पूर्णांक pkcs8_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा खुला_key *pub;

	pub = pkcs8_parse(prep->data, prep->datalen);
	अगर (IS_ERR(pub))
		वापस PTR_ERR(pub);

	pr_devel("Cert Key Algo: %s\n", pub->pkey_algo);
	pub->id_type = "PKCS8";

	/* We're pinning the module by being linked against it */
	__module_get(खुला_key_subtype.owner);
	prep->payload.data[asym_subtype] = &खुला_key_subtype;
	prep->payload.data[asym_key_ids] = शून्य;
	prep->payload.data[asym_crypto] = pub;
	prep->payload.data[asym_auth] = शून्य;
	prep->quotalen = 100;
	वापस 0;
पूर्ण

अटल काष्ठा asymmetric_key_parser pkcs8_key_parser = अणु
	.owner	= THIS_MODULE,
	.name	= "pkcs8",
	.parse	= pkcs8_key_preparse,
पूर्ण;

/*
 * Module stuff
 */
अटल पूर्णांक __init pkcs8_key_init(व्योम)
अणु
	वापस रेजिस्टर_asymmetric_key_parser(&pkcs8_key_parser);
पूर्ण

अटल व्योम __निकास pkcs8_key_निकास(व्योम)
अणु
	unरेजिस्टर_asymmetric_key_parser(&pkcs8_key_parser);
पूर्ण

module_init(pkcs8_key_init);
module_निकास(pkcs8_key_निकास);

MODULE_DESCRIPTION("PKCS#8 certificate parser");
MODULE_LICENSE("GPL");
