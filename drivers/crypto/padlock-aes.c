<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 
 * Cryptographic API.
 *
 * Support क्रम VIA PadLock hardware crypto engine.
 *
 * Copyright (c) 2004  Michal Ludvig <michal@logix.cz>
 *
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/padlock.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu/api.h>

/*
 * Number of data blocks actually fetched क्रम each xcrypt insn.
 * Processors with prefetch errata will fetch extra blocks.
 */
अटल अचिन्हित पूर्णांक ecb_fetch_blocks = 2;
#घोषणा MAX_ECB_FETCH_BLOCKS (8)
#घोषणा ecb_fetch_bytes (ecb_fetch_blocks * AES_BLOCK_SIZE)

अटल अचिन्हित पूर्णांक cbc_fetch_blocks = 1;
#घोषणा MAX_CBC_FETCH_BLOCKS (4)
#घोषणा cbc_fetch_bytes (cbc_fetch_blocks * AES_BLOCK_SIZE)

/* Control word. */
काष्ठा cword अणु
	अचिन्हित पूर्णांक __attribute__ ((__packed__))
		rounds:4,
		algo:3,
		keygen:1,
		पूर्णांकerm:1,
		encdec:1,
		ksize:2;
पूर्ण __attribute__ ((__aligned__(PADLOCK_ALIGNMENT)));

/* Whenever making any changes to the following
 * काष्ठाure *make sure* you keep E, d_data
 * and cword aligned on 16 Bytes boundaries and
 * the Hardware can access 16 * 16 bytes of E and d_data
 * (only the first 15 * 16 bytes matter but the HW पढ़ोs
 * more).
 */
काष्ठा aes_ctx अणु
	u32 E[AES_MAX_KEYLENGTH_U32]
		__attribute__ ((__aligned__(PADLOCK_ALIGNMENT)));
	u32 d_data[AES_MAX_KEYLENGTH_U32]
		__attribute__ ((__aligned__(PADLOCK_ALIGNMENT)));
	काष्ठा अणु
		काष्ठा cword encrypt;
		काष्ठा cword decrypt;
	पूर्ण cword;
	u32 *D;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cword *, paes_last_cword);

/* Tells whether the ACE is capable to generate
   the extended key क्रम a given key_len. */
अटल अंतरभूत पूर्णांक
aes_hw_extkey_available(uपूर्णांक8_t key_len)
अणु
	/* TODO: We should check the actual CPU model/stepping
	         as it's possible that the capability will be
	         added in the next CPU revisions. */
	अगर (key_len == 16)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा aes_ctx *aes_ctx_common(व्योम *ctx)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)ctx;
	अचिन्हित दीर्घ align = PADLOCK_ALIGNMENT;

	अगर (align <= crypto_tfm_ctx_alignment())
		align = 1;
	वापस (काष्ठा aes_ctx *)ALIGN(addr, align);
पूर्ण

अटल अंतरभूत काष्ठा aes_ctx *aes_ctx(काष्ठा crypto_tfm *tfm)
अणु
	वापस aes_ctx_common(crypto_tfm_ctx(tfm));
पूर्ण

अटल अंतरभूत काष्ठा aes_ctx *skcipher_aes_ctx(काष्ठा crypto_skcipher *tfm)
अणु
	वापस aes_ctx_common(crypto_skcipher_ctx(tfm));
पूर्ण

अटल पूर्णांक aes_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा aes_ctx *ctx = aes_ctx(tfm);
	स्थिर __le32 *key = (स्थिर __le32 *)in_key;
	काष्ठा crypto_aes_ctx gen_aes;
	पूर्णांक cpu;

	अगर (key_len % 8)
		वापस -EINVAL;

	/*
	 * If the hardware is capable of generating the extended key
	 * itself we must supply the plain key क्रम both encryption
	 * and decryption.
	 */
	ctx->D = ctx->E;

	ctx->E[0] = le32_to_cpu(key[0]);
	ctx->E[1] = le32_to_cpu(key[1]);
	ctx->E[2] = le32_to_cpu(key[2]);
	ctx->E[3] = le32_to_cpu(key[3]);

	/* Prepare control words. */
	स_रखो(&ctx->cword, 0, माप(ctx->cword));

	ctx->cword.decrypt.encdec = 1;
	ctx->cword.encrypt.rounds = 10 + (key_len - 16) / 4;
	ctx->cword.decrypt.rounds = ctx->cword.encrypt.rounds;
	ctx->cword.encrypt.ksize = (key_len - 16) / 8;
	ctx->cword.decrypt.ksize = ctx->cword.encrypt.ksize;

	/* Don't generate extended keys अगर the hardware can करो it. */
	अगर (aes_hw_extkey_available(key_len))
		जाओ ok;

	ctx->D = ctx->d_data;
	ctx->cword.encrypt.keygen = 1;
	ctx->cword.decrypt.keygen = 1;

	अगर (aes_expandkey(&gen_aes, in_key, key_len))
		वापस -EINVAL;

	स_नकल(ctx->E, gen_aes.key_enc, AES_MAX_KEYLENGTH);
	स_नकल(ctx->D, gen_aes.key_dec, AES_MAX_KEYLENGTH);

ok:
	क्रम_each_online_cpu(cpu)
		अगर (&ctx->cword.encrypt == per_cpu(paes_last_cword, cpu) ||
		    &ctx->cword.decrypt == per_cpu(paes_last_cword, cpu))
			per_cpu(paes_last_cword, cpu) = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक aes_set_key_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
				अचिन्हित पूर्णांक key_len)
अणु
	वापस aes_set_key(crypto_skcipher_tfm(tfm), in_key, key_len);
पूर्ण

/* ====== Encryption/decryption routines ====== */

/* These are the real call to PadLock. */
अटल अंतरभूत व्योम padlock_reset_key(काष्ठा cword *cword)
अणु
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (cword != per_cpu(paes_last_cword, cpu))
#अगर_अघोषित CONFIG_X86_64
		यंत्र अस्थिर ("pushfl; popfl");
#अन्यथा
		यंत्र अस्थिर ("pushfq; popfq");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम padlock_store_cword(काष्ठा cword *cword)
अणु
	per_cpu(paes_last_cword, raw_smp_processor_id()) = cword;
पूर्ण

/*
 * While the padlock inकाष्ठाions करोn't use FP/SSE रेजिस्टरs, they
 * generate a spurious DNA fault when CR0.TS is '1'.  Fortunately,
 * the kernel करोesn't use CR0.TS.
 */

अटल अंतरभूत व्योम rep_xcrypt_ecb(स्थिर u8 *input, u8 *output, व्योम *key,
				  काष्ठा cword *control_word, पूर्णांक count)
अणु
	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xc8"	/* rep xcryptecb */
		      : "+S"(input), "+D"(output)
		      : "d"(control_word), "b"(key), "c"(count));
पूर्ण

अटल अंतरभूत u8 *rep_xcrypt_cbc(स्थिर u8 *input, u8 *output, व्योम *key,
				 u8 *iv, काष्ठा cword *control_word, पूर्णांक count)
अणु
	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (control_word), "b" (key), "c" (count));
	वापस iv;
पूर्ण

अटल व्योम ecb_crypt_copy(स्थिर u8 *in, u8 *out, u32 *key,
			   काष्ठा cword *cword, पूर्णांक count)
अणु
	/*
	 * Padlock prefetches extra data so we must provide mapped input buffers.
	 * Assume there are at least 16 bytes of stack alपढ़ोy in use.
	 */
	u8 buf[AES_BLOCK_SIZE * (MAX_ECB_FETCH_BLOCKS - 1) + PADLOCK_ALIGNMENT - 1];
	u8 *पंचांगp = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);

	स_नकल(पंचांगp, in, count * AES_BLOCK_SIZE);
	rep_xcrypt_ecb(पंचांगp, out, key, cword, count);
पूर्ण

अटल u8 *cbc_crypt_copy(स्थिर u8 *in, u8 *out, u32 *key,
			   u8 *iv, काष्ठा cword *cword, पूर्णांक count)
अणु
	/*
	 * Padlock prefetches extra data so we must provide mapped input buffers.
	 * Assume there are at least 16 bytes of stack alपढ़ोy in use.
	 */
	u8 buf[AES_BLOCK_SIZE * (MAX_CBC_FETCH_BLOCKS - 1) + PADLOCK_ALIGNMENT - 1];
	u8 *पंचांगp = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);

	स_नकल(पंचांगp, in, count * AES_BLOCK_SIZE);
	वापस rep_xcrypt_cbc(पंचांगp, out, key, iv, cword, count);
पूर्ण

अटल अंतरभूत व्योम ecb_crypt(स्थिर u8 *in, u8 *out, u32 *key,
			     काष्ठा cword *cword, पूर्णांक count)
अणु
	/* Padlock in ECB mode fetches at least ecb_fetch_bytes of data.
	 * We could aव्योम some copying here but it's probably not worth it.
	 */
	अगर (unlikely(offset_in_page(in) + ecb_fetch_bytes > PAGE_SIZE)) अणु
		ecb_crypt_copy(in, out, key, cword, count);
		वापस;
	पूर्ण

	rep_xcrypt_ecb(in, out, key, cword, count);
पूर्ण

अटल अंतरभूत u8 *cbc_crypt(स्थिर u8 *in, u8 *out, u32 *key,
			    u8 *iv, काष्ठा cword *cword, पूर्णांक count)
अणु
	/* Padlock in CBC mode fetches at least cbc_fetch_bytes of data. */
	अगर (unlikely(offset_in_page(in) + cbc_fetch_bytes > PAGE_SIZE))
		वापस cbc_crypt_copy(in, out, key, iv, cword, count);

	वापस rep_xcrypt_cbc(in, out, key, iv, cword, count);
पूर्ण

अटल अंतरभूत व्योम padlock_xcrypt_ecb(स्थिर u8 *input, u8 *output, व्योम *key,
				      व्योम *control_word, u32 count)
अणु
	u32 initial = count & (ecb_fetch_blocks - 1);

	अगर (count < ecb_fetch_blocks) अणु
		ecb_crypt(input, output, key, control_word, count);
		वापस;
	पूर्ण

	count -= initial;

	अगर (initial)
		यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xc8"	/* rep xcryptecb */
			      : "+S"(input), "+D"(output)
			      : "d"(control_word), "b"(key), "c"(initial));

	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xc8"	/* rep xcryptecb */
		      : "+S"(input), "+D"(output)
		      : "d"(control_word), "b"(key), "c"(count));
पूर्ण

अटल अंतरभूत u8 *padlock_xcrypt_cbc(स्थिर u8 *input, u8 *output, व्योम *key,
				     u8 *iv, व्योम *control_word, u32 count)
अणु
	u32 initial = count & (cbc_fetch_blocks - 1);

	अगर (count < cbc_fetch_blocks)
		वापस cbc_crypt(input, output, key, iv, control_word, count);

	count -= initial;

	अगर (initial)
		यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
			      : "+S" (input), "+D" (output), "+a" (iv)
			      : "d" (control_word), "b" (key), "c" (initial));

	यंत्र अस्थिर (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (control_word), "b" (key), "c" (count));
	वापस iv;
पूर्ण

अटल व्योम padlock_aes_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा aes_ctx *ctx = aes_ctx(tfm);

	padlock_reset_key(&ctx->cword.encrypt);
	ecb_crypt(in, out, ctx->E, &ctx->cword.encrypt, 1);
	padlock_store_cword(&ctx->cword.encrypt);
पूर्ण

अटल व्योम padlock_aes_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा aes_ctx *ctx = aes_ctx(tfm);

	padlock_reset_key(&ctx->cword.encrypt);
	ecb_crypt(in, out, ctx->D, &ctx->cword.decrypt, 1);
	padlock_store_cword(&ctx->cword.encrypt);
पूर्ण

अटल काष्ठा crypto_alg aes_alg = अणु
	.cra_name		=	"aes",
	.cra_driver_name	=	"aes-padlock",
	.cra_priority		=	PADLOCK_CRA_PRIORITY,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा aes_ctx),
	.cra_alignmask		=	PADLOCK_ALIGNMENT - 1,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey	   	= 	aes_set_key,
			.cia_encrypt	 	=	padlock_aes_encrypt,
			.cia_decrypt	  	=	padlock_aes_decrypt,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक ecb_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aes_ctx *ctx = skcipher_aes_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	padlock_reset_key(&ctx->cword.encrypt);

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		padlock_xcrypt_ecb(walk.src.virt.addr, walk.dst.virt.addr,
				   ctx->E, &ctx->cword.encrypt,
				   nbytes / AES_BLOCK_SIZE);
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	padlock_store_cword(&ctx->cword.encrypt);

	वापस err;
पूर्ण

अटल पूर्णांक ecb_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aes_ctx *ctx = skcipher_aes_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	padlock_reset_key(&ctx->cword.decrypt);

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		padlock_xcrypt_ecb(walk.src.virt.addr, walk.dst.virt.addr,
				   ctx->D, &ctx->cword.decrypt,
				   nbytes / AES_BLOCK_SIZE);
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	padlock_store_cword(&ctx->cword.encrypt);

	वापस err;
पूर्ण

अटल काष्ठा skcipher_alg ecb_aes_alg = अणु
	.base.cra_name		=	"ecb(aes)",
	.base.cra_driver_name	=	"ecb-aes-padlock",
	.base.cra_priority	=	PADLOCK_COMPOSITE_PRIORITY,
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा aes_ctx),
	.base.cra_alignmask	=	PADLOCK_ALIGNMENT - 1,
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.setkey			=	aes_set_key_skcipher,
	.encrypt		=	ecb_aes_encrypt,
	.decrypt		=	ecb_aes_decrypt,
पूर्ण;

अटल पूर्णांक cbc_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aes_ctx *ctx = skcipher_aes_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	padlock_reset_key(&ctx->cword.encrypt);

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		u8 *iv = padlock_xcrypt_cbc(walk.src.virt.addr,
					    walk.dst.virt.addr, ctx->E,
					    walk.iv, &ctx->cword.encrypt,
					    nbytes / AES_BLOCK_SIZE);
		स_नकल(walk.iv, iv, AES_BLOCK_SIZE);
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	padlock_store_cword(&ctx->cword.decrypt);

	वापस err;
पूर्ण

अटल पूर्णांक cbc_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा aes_ctx *ctx = skcipher_aes_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	padlock_reset_key(&ctx->cword.encrypt);

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		padlock_xcrypt_cbc(walk.src.virt.addr, walk.dst.virt.addr,
				   ctx->D, walk.iv, &ctx->cword.decrypt,
				   nbytes / AES_BLOCK_SIZE);
		nbytes &= AES_BLOCK_SIZE - 1;
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	padlock_store_cword(&ctx->cword.encrypt);

	वापस err;
पूर्ण

अटल काष्ठा skcipher_alg cbc_aes_alg = अणु
	.base.cra_name		=	"cbc(aes)",
	.base.cra_driver_name	=	"cbc-aes-padlock",
	.base.cra_priority	=	PADLOCK_COMPOSITE_PRIORITY,
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा aes_ctx),
	.base.cra_alignmask	=	PADLOCK_ALIGNMENT - 1,
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	aes_set_key_skcipher,
	.encrypt		=	cbc_aes_encrypt,
	.decrypt		=	cbc_aes_decrypt,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id padlock_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_XCRYPT, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, padlock_cpu_id);

अटल पूर्णांक __init padlock_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	अगर (!x86_match_cpu(padlock_cpu_id))
		वापस -ENODEV;

	अगर (!boot_cpu_has(X86_FEATURE_XCRYPT_EN)) अणु
		prपूर्णांकk(KERN_NOTICE PFX "VIA PadLock detected, but not enabled. Hmm, strange...\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((ret = crypto_रेजिस्टर_alg(&aes_alg)) != 0)
		जाओ aes_err;

	अगर ((ret = crypto_रेजिस्टर_skcipher(&ecb_aes_alg)) != 0)
		जाओ ecb_aes_err;

	अगर ((ret = crypto_रेजिस्टर_skcipher(&cbc_aes_alg)) != 0)
		जाओ cbc_aes_err;

	prपूर्णांकk(KERN_NOTICE PFX "Using VIA PadLock ACE for AES algorithm.\n");

	अगर (c->x86 == 6 && c->x86_model == 15 && c->x86_stepping == 2) अणु
		ecb_fetch_blocks = MAX_ECB_FETCH_BLOCKS;
		cbc_fetch_blocks = MAX_CBC_FETCH_BLOCKS;
		prपूर्णांकk(KERN_NOTICE PFX "VIA Nano stepping 2 detected: enabling workaround.\n");
	पूर्ण

out:
	वापस ret;

cbc_aes_err:
	crypto_unरेजिस्टर_skcipher(&ecb_aes_alg);
ecb_aes_err:
	crypto_unरेजिस्टर_alg(&aes_alg);
aes_err:
	prपूर्णांकk(KERN_ERR PFX "VIA PadLock AES initialization failed.\n");
	जाओ out;
पूर्ण

अटल व्योम __निकास padlock_fini(व्योम)
अणु
	crypto_unरेजिस्टर_skcipher(&cbc_aes_alg);
	crypto_unरेजिस्टर_skcipher(&ecb_aes_alg);
	crypto_unरेजिस्टर_alg(&aes_alg);
पूर्ण

module_init(padlock_init);
module_निकास(padlock_fini);

MODULE_DESCRIPTION("VIA PadLock AES algorithm support");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Ludvig");

MODULE_ALIAS_CRYPTO("aes");
