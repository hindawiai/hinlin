<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "TPM-PARSER: "fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <keys/asymmetric-subtype.h>
#समावेश <keys/asymmetric-parser.h>
#समावेश <crypto/asym_tpm_subtype.h>
#समावेश "tpm.asn1.h"

काष्ठा tpm_parse_context अणु
	स्थिर व्योम	*blob;
	u32		blob_len;
पूर्ण;

/*
 * Note the key data of the ASN.1 blob.
 */
पूर्णांक tpm_note_key(व्योम *context, माप_प्रकार hdrlen,
		   अचिन्हित अक्षर tag,
		   स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा tpm_parse_context *ctx = context;

	ctx->blob = value;
	ctx->blob_len = vlen;

	वापस 0;
पूर्ण

/*
 * Parse a TPM-encrypted निजी key blob.
 */
अटल काष्ठा tpm_key *tpm_parse(स्थिर व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा tpm_parse_context ctx;
	दीर्घ ret;

	स_रखो(&ctx, 0, माप(ctx));

	/* Attempt to decode the निजी key */
	ret = asn1_ber_decoder(&tpm_decoder, &ctx, data, datalen);
	अगर (ret < 0)
		जाओ error;

	वापस tpm_key_create(ctx.blob, ctx.blob_len);

error:
	वापस ERR_PTR(ret);
पूर्ण
/*
 * Attempt to parse a data blob क्रम a key as a TPM निजी key blob.
 */
अटल पूर्णांक tpm_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा tpm_key *tk;

	/*
	 * TPM 1.2 keys are max 2048 bits दीर्घ, so assume the blob is no
	 * more than 4x that
	 */
	अगर (prep->datalen > 256 * 4)
		वापस -EMSGSIZE;

	tk = tpm_parse(prep->data, prep->datalen);

	अगर (IS_ERR(tk))
		वापस PTR_ERR(tk);

	/* We're pinning the module by being linked against it */
	__module_get(asym_tpm_subtype.owner);
	prep->payload.data[asym_subtype] = &asym_tpm_subtype;
	prep->payload.data[asym_key_ids] = शून्य;
	prep->payload.data[asym_crypto] = tk;
	prep->payload.data[asym_auth] = शून्य;
	prep->quotalen = 100;
	वापस 0;
पूर्ण

अटल काष्ठा asymmetric_key_parser tpm_key_parser = अणु
	.owner	= THIS_MODULE,
	.name	= "tpm_parser",
	.parse	= tpm_key_preparse,
पूर्ण;

अटल पूर्णांक __init tpm_key_init(व्योम)
अणु
	वापस रेजिस्टर_asymmetric_key_parser(&tpm_key_parser);
पूर्ण

अटल व्योम __निकास tpm_key_निकास(व्योम)
अणु
	unरेजिस्टर_asymmetric_key_parser(&tpm_key_parser);
पूर्ण

module_init(tpm_key_init);
module_निकास(tpm_key_निकास);

MODULE_DESCRIPTION("TPM private key-blob parser");
MODULE_LICENSE("GPL v2");
