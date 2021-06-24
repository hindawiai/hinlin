<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Support क्रम VIA PadLock hardware crypto engine.
 *
 * Copyright (c) 2006  Michal Ludvig <michal@logix.cz>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/padlock.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/fpu/api.h>

काष्ठा padlock_sha_desc अणु
	काष्ठा shash_desc fallback;
पूर्ण;

काष्ठा padlock_sha_ctx अणु
	काष्ठा crypto_shash *fallback;
पूर्ण;

अटल पूर्णांक padlock_sha_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);
	काष्ठा padlock_sha_ctx *ctx = crypto_shash_ctx(desc->tfm);

	dctx->fallback.tfm = ctx->fallback;
	वापस crypto_shash_init(&dctx->fallback);
पूर्ण

अटल पूर्णांक padlock_sha_update(काष्ठा shash_desc *desc,
			      स्थिर u8 *data, अचिन्हित पूर्णांक length)
अणु
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);

	वापस crypto_shash_update(&dctx->fallback, data, length);
पूर्ण

अटल पूर्णांक padlock_sha_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);

	वापस crypto_shash_export(&dctx->fallback, out);
पूर्ण

अटल पूर्णांक padlock_sha_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);
	काष्ठा padlock_sha_ctx *ctx = crypto_shash_ctx(desc->tfm);

	dctx->fallback.tfm = ctx->fallback;
	वापस crypto_shash_import(&dctx->fallback, in);
पूर्ण

अटल अंतरभूत व्योम padlock_output_block(uपूर्णांक32_t *src,
		 	uपूर्णांक32_t *dst, माप_प्रकार count)
अणु
	जबतक (count--)
		*dst++ = swab32(*src++);
पूर्ण

अटल पूर्णांक padlock_sha1_finup(काष्ठा shash_desc *desc, स्थिर u8 *in,
			      अचिन्हित पूर्णांक count, u8 *out)
अणु
	/* We can't store directly to *out as it may be unaligned. */
	/* BTW Don't reduce the buffer size below 128 Bytes!
	 *     PadLock microcode needs it that big. */
	अक्षर buf[128 + PADLOCK_ALIGNMENT - STACK_ALIGN] __attribute__
		((aligned(STACK_ALIGN)));
	अक्षर *result = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);
	काष्ठा sha1_state state;
	अचिन्हित पूर्णांक space;
	अचिन्हित पूर्णांक leftover;
	पूर्णांक err;

	err = crypto_shash_export(&dctx->fallback, &state);
	अगर (err)
		जाओ out;

	अगर (state.count + count > अच_दीर्घ_उच्च)
		वापस crypto_shash_finup(&dctx->fallback, in, count, out);

	leftover = ((state.count - 1) & (SHA1_BLOCK_SIZE - 1)) + 1;
	space =  SHA1_BLOCK_SIZE - leftover;
	अगर (space) अणु
		अगर (count > space) अणु
			err = crypto_shash_update(&dctx->fallback, in, space) ?:
			      crypto_shash_export(&dctx->fallback, &state);
			अगर (err)
				जाओ out;
			count -= space;
			in += space;
		पूर्ण अन्यथा अणु
			स_नकल(state.buffer + leftover, in, count);
			in = state.buffer;
			count += leftover;
			state.count &= ~(SHA1_BLOCK_SIZE - 1);
		पूर्ण
	पूर्ण

	स_नकल(result, &state.state, SHA1_DIGEST_SIZE);

	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xc8" /* rep xsha1 */
		      : \
		      : "c"((अचिन्हित दीर्घ)state.count + count), \
			"a"((अचिन्हित दीर्घ)state.count), \
			"S"(in), "D"(result));

	padlock_output_block((uपूर्णांक32_t *)result, (uपूर्णांक32_t *)out, 5);

out:
	वापस err;
पूर्ण

अटल पूर्णांक padlock_sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u8 buf[4];

	वापस padlock_sha1_finup(desc, buf, 0, out);
पूर्ण

अटल पूर्णांक padlock_sha256_finup(काष्ठा shash_desc *desc, स्थिर u8 *in,
				अचिन्हित पूर्णांक count, u8 *out)
अणु
	/* We can't store directly to *out as it may be unaligned. */
	/* BTW Don't reduce the buffer size below 128 Bytes!
	 *     PadLock microcode needs it that big. */
	अक्षर buf[128 + PADLOCK_ALIGNMENT - STACK_ALIGN] __attribute__
		((aligned(STACK_ALIGN)));
	अक्षर *result = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);
	काष्ठा padlock_sha_desc *dctx = shash_desc_ctx(desc);
	काष्ठा sha256_state state;
	अचिन्हित पूर्णांक space;
	अचिन्हित पूर्णांक leftover;
	पूर्णांक err;

	err = crypto_shash_export(&dctx->fallback, &state);
	अगर (err)
		जाओ out;

	अगर (state.count + count > अच_दीर्घ_उच्च)
		वापस crypto_shash_finup(&dctx->fallback, in, count, out);

	leftover = ((state.count - 1) & (SHA256_BLOCK_SIZE - 1)) + 1;
	space =  SHA256_BLOCK_SIZE - leftover;
	अगर (space) अणु
		अगर (count > space) अणु
			err = crypto_shash_update(&dctx->fallback, in, space) ?:
			      crypto_shash_export(&dctx->fallback, &state);
			अगर (err)
				जाओ out;
			count -= space;
			in += space;
		पूर्ण अन्यथा अणु
			स_नकल(state.buf + leftover, in, count);
			in = state.buf;
			count += leftover;
			state.count &= ~(SHA1_BLOCK_SIZE - 1);
		पूर्ण
	पूर्ण

	स_नकल(result, &state.state, SHA256_DIGEST_SIZE);

	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xd0" /* rep xsha256 */
		      : \
		      : "c"((अचिन्हित दीर्घ)state.count + count), \
			"a"((अचिन्हित दीर्घ)state.count), \
			"S"(in), "D"(result));

	padlock_output_block((uपूर्णांक32_t *)result, (uपूर्णांक32_t *)out, 8);

out:
	वापस err;
पूर्ण

अटल पूर्णांक padlock_sha256_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u8 buf[4];

	वापस padlock_sha256_finup(desc, buf, 0, out);
पूर्ण

अटल पूर्णांक padlock_init_tfm(काष्ठा crypto_shash *hash)
अणु
	स्थिर अक्षर *fallback_driver_name = crypto_shash_alg_name(hash);
	काष्ठा padlock_sha_ctx *ctx = crypto_shash_ctx(hash);
	काष्ठा crypto_shash *fallback_tfm;

	/* Allocate a fallback and पात अगर it failed. */
	fallback_tfm = crypto_alloc_shash(fallback_driver_name, 0,
					  CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback_tfm)) अणु
		prपूर्णांकk(KERN_WARNING PFX "Fallback driver '%s' could not be loaded!\n",
		       fallback_driver_name);
		वापस PTR_ERR(fallback_tfm);
	पूर्ण

	ctx->fallback = fallback_tfm;
	hash->descsize += crypto_shash_descsize(fallback_tfm);
	वापस 0;
पूर्ण

अटल व्योम padlock_निकास_tfm(काष्ठा crypto_shash *hash)
अणु
	काष्ठा padlock_sha_ctx *ctx = crypto_shash_ctx(hash);

	crypto_मुक्त_shash(ctx->fallback);
पूर्ण

अटल काष्ठा shash_alg sha1_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init   	= 	padlock_sha_init,
	.update 	=	padlock_sha_update,
	.finup  	=	padlock_sha1_finup,
	.final  	=	padlock_sha1_final,
	.export		=	padlock_sha_export,
	.import		=	padlock_sha_import,
	.init_tfm	=	padlock_init_tfm,
	.निकास_tfm	=	padlock_निकास_tfm,
	.descsize	=	माप(काष्ठा padlock_sha_desc),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name		=	"sha1",
		.cra_driver_name	=	"sha1-padlock",
		.cra_priority		=	PADLOCK_CRA_PRIORITY,
		.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		=	SHA1_BLOCK_SIZE,
		.cra_ctxsize		=	माप(काष्ठा padlock_sha_ctx),
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा shash_alg sha256_alg = अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init   	= 	padlock_sha_init,
	.update 	=	padlock_sha_update,
	.finup  	=	padlock_sha256_finup,
	.final  	=	padlock_sha256_final,
	.export		=	padlock_sha_export,
	.import		=	padlock_sha_import,
	.init_tfm	=	padlock_init_tfm,
	.निकास_tfm	=	padlock_निकास_tfm,
	.descsize	=	माप(काष्ठा padlock_sha_desc),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name		=	"sha256",
		.cra_driver_name	=	"sha256-padlock",
		.cra_priority		=	PADLOCK_CRA_PRIORITY,
		.cra_flags		=	CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		=	SHA256_BLOCK_SIZE,
		.cra_ctxsize		=	माप(काष्ठा padlock_sha_ctx),
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

/* Add two shash_alg instance क्रम hardware-implemented *
* multiple-parts hash supported by VIA Nano Processor.*/
अटल पूर्णांक padlock_sha1_init_nano(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	*sctx = (काष्ठा sha1_state)अणु
		.state = अणु SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4 पूर्ण,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha1_update_nano(काष्ठा shash_desc *desc,
			स्थिर u8 *data,	अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial, करोne;
	स्थिर u8 *src;
	/*The PHE require the out buffer must 128 bytes and 16-bytes aligned*/
	u8 buf[128 + PADLOCK_ALIGNMENT - STACK_ALIGN] __attribute__
		((aligned(STACK_ALIGN)));
	u8 *dst = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);

	partial = sctx->count & 0x3f;
	sctx->count += len;
	करोne = 0;
	src = data;
	स_नकल(dst, (u8 *)(sctx->state), SHA1_DIGEST_SIZE);

	अगर ((partial + len) >= SHA1_BLOCK_SIZE) अणु

		/* Append the bytes in state's buffer to a block to handle */
		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buffer + partial, data,
				करोne + SHA1_BLOCK_SIZE);
			src = sctx->buffer;
			यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xc8"
			: "+S"(src), "+D"(dst) \
			: "a"((दीर्घ)-1), "c"((अचिन्हित दीर्घ)1));
			करोne += SHA1_BLOCK_SIZE;
			src = data + करोne;
		पूर्ण

		/* Process the left bytes from the input data */
		अगर (len - करोne >= SHA1_BLOCK_SIZE) अणु
			यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xc8"
			: "+S"(src), "+D"(dst)
			: "a"((दीर्घ)-1),
			"c"((अचिन्हित दीर्घ)((len - करोne) / SHA1_BLOCK_SIZE)));
			करोne += ((len - करोne) - (len - करोne) % SHA1_BLOCK_SIZE);
			src = data + करोne;
		पूर्ण
		partial = 0;
	पूर्ण
	स_नकल((u8 *)(sctx->state), dst, SHA1_DIGEST_SIZE);
	स_नकल(sctx->buffer + partial, src, len - करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha1_final_nano(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *state = (काष्ठा sha1_state *)shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial, padlen;
	__be64 bits;
	अटल स्थिर u8 padding[64] = अणु 0x80, पूर्ण;

	bits = cpu_to_be64(state->count << 3);

	/* Pad out to 56 mod 64 */
	partial = state->count & 0x3f;
	padlen = (partial < 56) ? (56 - partial) : ((64+56) - partial);
	padlock_sha1_update_nano(desc, padding, padlen);

	/* Append length field bytes */
	padlock_sha1_update_nano(desc, (स्थिर u8 *)&bits, माप(bits));

	/* Swap to output */
	padlock_output_block((uपूर्णांक32_t *)(state->state), (uपूर्णांक32_t *)out, 5);

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha256_init_nano(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	*sctx = (काष्ठा sha256_state)अणु
		.state = अणु SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3, \
				SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7पूर्ण,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha256_update_nano(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial, करोne;
	स्थिर u8 *src;
	/*The PHE require the out buffer must 128 bytes and 16-bytes aligned*/
	u8 buf[128 + PADLOCK_ALIGNMENT - STACK_ALIGN] __attribute__
		((aligned(STACK_ALIGN)));
	u8 *dst = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);

	partial = sctx->count & 0x3f;
	sctx->count += len;
	करोne = 0;
	src = data;
	स_नकल(dst, (u8 *)(sctx->state), SHA256_DIGEST_SIZE);

	अगर ((partial + len) >= SHA256_BLOCK_SIZE) अणु

		/* Append the bytes in state's buffer to a block to handle */
		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buf + partial, data,
				करोne + SHA256_BLOCK_SIZE);
			src = sctx->buf;
			यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xd0"
			: "+S"(src), "+D"(dst)
			: "a"((दीर्घ)-1), "c"((अचिन्हित दीर्घ)1));
			करोne += SHA256_BLOCK_SIZE;
			src = data + करोne;
		पूर्ण

		/* Process the left bytes from input data*/
		अगर (len - करोne >= SHA256_BLOCK_SIZE) अणु
			यंत्र अस्थिर (".byte 0xf3,0x0f,0xa6,0xd0"
			: "+S"(src), "+D"(dst)
			: "a"((दीर्घ)-1),
			"c"((अचिन्हित दीर्घ)((len - करोne) / 64)));
			करोne += ((len - करोne) - (len - करोne) % 64);
			src = data + करोne;
		पूर्ण
		partial = 0;
	पूर्ण
	स_नकल((u8 *)(sctx->state), dst, SHA256_DIGEST_SIZE);
	स_नकल(sctx->buf + partial, src, len - करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha256_final_nano(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha256_state *state =
		(काष्ठा sha256_state *)shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial, padlen;
	__be64 bits;
	अटल स्थिर u8 padding[64] = अणु 0x80, पूर्ण;

	bits = cpu_to_be64(state->count << 3);

	/* Pad out to 56 mod 64 */
	partial = state->count & 0x3f;
	padlen = (partial < 56) ? (56 - partial) : ((64+56) - partial);
	padlock_sha256_update_nano(desc, padding, padlen);

	/* Append length field bytes */
	padlock_sha256_update_nano(desc, (स्थिर u8 *)&bits, माप(bits));

	/* Swap to output */
	padlock_output_block((uपूर्णांक32_t *)(state->state), (uपूर्णांक32_t *)out, 8);

	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha_export_nano(काष्ठा shash_desc *desc,
				व्योम *out)
अणु
	पूर्णांक statesize = crypto_shash_statesize(desc->tfm);
	व्योम *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, statesize);
	वापस 0;
पूर्ण

अटल पूर्णांक padlock_sha_import_nano(काष्ठा shash_desc *desc,
				स्थिर व्योम *in)
अणु
	पूर्णांक statesize = crypto_shash_statesize(desc->tfm);
	व्योम *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, statesize);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha1_alg_nano = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	padlock_sha1_init_nano,
	.update		=	padlock_sha1_update_nano,
	.final		=	padlock_sha1_final_nano,
	.export		=	padlock_sha_export_nano,
	.import		=	padlock_sha_import_nano,
	.descsize	=	माप(काष्ठा sha1_state),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name		=	"sha1",
		.cra_driver_name	=	"sha1-padlock-nano",
		.cra_priority		=	PADLOCK_CRA_PRIORITY,
		.cra_blocksize		=	SHA1_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा shash_alg sha256_alg_nano = अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	padlock_sha256_init_nano,
	.update		=	padlock_sha256_update_nano,
	.final		=	padlock_sha256_final_nano,
	.export		=	padlock_sha_export_nano,
	.import		=	padlock_sha_import_nano,
	.descsize	=	माप(काष्ठा sha256_state),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name		=	"sha256",
		.cra_driver_name	=	"sha256-padlock-nano",
		.cra_priority		=	PADLOCK_CRA_PRIORITY,
		.cra_blocksize		=	SHA256_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id padlock_sha_ids[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_PHE, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, padlock_sha_ids);

अटल पूर्णांक __init padlock_init(व्योम)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	काष्ठा shash_alg *sha1;
	काष्ठा shash_alg *sha256;

	अगर (!x86_match_cpu(padlock_sha_ids) || !boot_cpu_has(X86_FEATURE_PHE_EN))
		वापस -ENODEV;

	/* Register the newly added algorithm module अगर on *
	* VIA Nano processor, or अन्यथा just करो as beक्रमe */
	अगर (c->x86_model < 0x0f) अणु
		sha1 = &sha1_alg;
		sha256 = &sha256_alg;
	पूर्ण अन्यथा अणु
		sha1 = &sha1_alg_nano;
		sha256 = &sha256_alg_nano;
	पूर्ण

	rc = crypto_रेजिस्टर_shash(sha1);
	अगर (rc)
		जाओ out;

	rc = crypto_रेजिस्टर_shash(sha256);
	अगर (rc)
		जाओ out_unreg1;

	prपूर्णांकk(KERN_NOTICE PFX "Using VIA PadLock ACE for SHA1/SHA256 algorithms.\n");

	वापस 0;

out_unreg1:
	crypto_unरेजिस्टर_shash(sha1);

out:
	prपूर्णांकk(KERN_ERR PFX "VIA PadLock SHA1/SHA256 initialization failed.\n");
	वापस rc;
पूर्ण

अटल व्योम __निकास padlock_fini(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	अगर (c->x86_model >= 0x0f) अणु
		crypto_unरेजिस्टर_shash(&sha1_alg_nano);
		crypto_unरेजिस्टर_shash(&sha256_alg_nano);
	पूर्ण अन्यथा अणु
		crypto_unरेजिस्टर_shash(&sha1_alg);
		crypto_unरेजिस्टर_shash(&sha256_alg);
	पूर्ण
पूर्ण

module_init(padlock_init);
module_निकास(padlock_fini);

MODULE_DESCRIPTION("VIA PadLock SHA1/SHA256 algorithms support.");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Ludvig");

MODULE_ALIAS_CRYPTO("sha1-all");
MODULE_ALIAS_CRYPTO("sha256-all");
MODULE_ALIAS_CRYPTO("sha1-padlock");
MODULE_ALIAS_CRYPTO("sha256-padlock");
