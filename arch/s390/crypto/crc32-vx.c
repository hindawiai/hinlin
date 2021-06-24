<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Crypto-API module क्रम CRC-32 algorithms implemented with the
 * z/Architecture Vector Extension Facility.
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"crc32-vx"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crc32.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <यंत्र/fpu/api.h>


#घोषणा CRC32_BLOCK_SIZE	1
#घोषणा CRC32_DIGEST_SIZE	4

#घोषणा VX_MIN_LEN		64
#घोषणा VX_ALIGNMENT		16L
#घोषणा VX_ALIGN_MASK		(VX_ALIGNMENT - 1)

काष्ठा crc_ctx अणु
	u32 key;
पूर्ण;

काष्ठा crc_desc_ctx अणु
	u32 crc;
पूर्ण;

/* Prototypes क्रम functions in assembly files */
u32 crc32_le_vgfm_16(u32 crc, अचिन्हित अक्षर स्थिर *buf, माप_प्रकार size);
u32 crc32_be_vgfm_16(u32 crc, अचिन्हित अक्षर स्थिर *buf, माप_प्रकार size);
u32 crc32c_le_vgfm_16(u32 crc, अचिन्हित अक्षर स्थिर *buf, माप_प्रकार size);

/*
 * DEFINE_CRC32_VX() - Define a CRC-32 function using the vector extension
 *
 * Creates a function to perक्रमm a particular CRC-32 computation. Depending
 * on the message buffer, the hardware-accelerated or software implementation
 * is used.   Note that the message buffer is aligned to improve fetch
 * operations of VECTOR LOAD MULTIPLE inकाष्ठाions.
 *
 */
#घोषणा DEFINE_CRC32_VX(___fname, ___crc32_vx, ___crc32_sw)		    \
	अटल u32 __pure ___fname(u32 crc,				    \
				अचिन्हित अक्षर स्थिर *data, माप_प्रकार datalen)  \
	अणु								    \
		काष्ठा kernel_fpu vxstate;				    \
		अचिन्हित दीर्घ prealign, aligned, reमुख्यing;		    \
									    \
		अगर (datalen < VX_MIN_LEN + VX_ALIGN_MASK)		    \
			वापस ___crc32_sw(crc, data, datalen);		    \
									    \
		अगर ((अचिन्हित दीर्घ)data & VX_ALIGN_MASK) अणु		    \
			prealign = VX_ALIGNMENT -			    \
				  ((अचिन्हित दीर्घ)data & VX_ALIGN_MASK);    \
			datalen -= prealign;				    \
			crc = ___crc32_sw(crc, data, prealign);		    \
			data = (व्योम *)((अचिन्हित दीर्घ)data + prealign);    \
		पूर्ण							    \
									    \
		aligned = datalen & ~VX_ALIGN_MASK;			    \
		reमुख्यing = datalen & VX_ALIGN_MASK;			    \
									    \
		kernel_fpu_begin(&vxstate, KERNEL_VXR_LOW);		    \
		crc = ___crc32_vx(crc, data, aligned);			    \
		kernel_fpu_end(&vxstate, KERNEL_VXR_LOW);		    \
									    \
		अगर (reमुख्यing)						    \
			crc = ___crc32_sw(crc, data + aligned, reमुख्यing);  \
									    \
		वापस crc;						    \
	पूर्ण

DEFINE_CRC32_VX(crc32_le_vx, crc32_le_vgfm_16, crc32_le)
DEFINE_CRC32_VX(crc32_be_vx, crc32_be_vgfm_16, crc32_be)
DEFINE_CRC32_VX(crc32c_le_vx, crc32c_le_vgfm_16, __crc32c_le)


अटल पूर्णांक crc32_vx_cra_init_zero(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crc_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_vx_cra_init_invert(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crc_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = ~0;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_vx_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा crc_ctx *mctx = crypto_shash_ctx(desc->tfm);
	काष्ठा crc_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = mctx->key;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_vx_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *newkey,
			   अचिन्हित पूर्णांक newkeylen)
अणु
	काष्ठा crc_ctx *mctx = crypto_shash_ctx(tfm);

	अगर (newkeylen != माप(mctx->key))
		वापस -EINVAL;
	mctx->key = le32_to_cpu(*(__le32 *)newkey);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32be_vx_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *newkey,
			     अचिन्हित पूर्णांक newkeylen)
अणु
	काष्ठा crc_ctx *mctx = crypto_shash_ctx(tfm);

	अगर (newkeylen != माप(mctx->key))
		वापस -EINVAL;
	mctx->key = be32_to_cpu(*(__be32 *)newkey);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32le_vx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा crc_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__le32 *)out = cpu_to_le32p(&ctx->crc);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32be_vx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा crc_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__be32 *)out = cpu_to_be32p(&ctx->crc);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_vx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा crc_desc_ctx *ctx = shash_desc_ctx(desc);

	/*
	 * Perक्रमm a final XOR with 0xFFFFFFFF to be in sync
	 * with the generic crc32c shash implementation.
	 */
	*(__le32 *)out = ~cpu_to_le32p(&ctx->crc);
	वापस 0;
पूर्ण

अटल पूर्णांक __crc32le_vx_finup(u32 *crc, स्थिर u8 *data, अचिन्हित पूर्णांक len,
			      u8 *out)
अणु
	*(__le32 *)out = cpu_to_le32(crc32_le_vx(*crc, data, len));
	वापस 0;
पूर्ण

अटल पूर्णांक __crc32be_vx_finup(u32 *crc, स्थिर u8 *data, अचिन्हित पूर्णांक len,
			      u8 *out)
अणु
	*(__be32 *)out = cpu_to_be32(crc32_be_vx(*crc, data, len));
	वापस 0;
पूर्ण

अटल पूर्णांक __crc32c_vx_finup(u32 *crc, स्थिर u8 *data, अचिन्हित पूर्णांक len,
			     u8 *out)
अणु
	/*
	 * Perक्रमm a final XOR with 0xFFFFFFFF to be in sync
	 * with the generic crc32c shash implementation.
	 */
	*(__le32 *)out = ~cpu_to_le32(crc32c_le_vx(*crc, data, len));
	वापस 0;
पूर्ण


#घोषणा CRC32_VX_FINUP(alg, func)					      \
	अटल पूर्णांक alg ## _vx_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,  \
				   अचिन्हित पूर्णांक datalen, u8 *out)	      \
	अणु								      \
		वापस __ ## alg ## _vx_finup(shash_desc_ctx(desc),	      \
					      data, datalen, out);	      \
	पूर्ण

CRC32_VX_FINUP(crc32le, crc32_le_vx)
CRC32_VX_FINUP(crc32be, crc32_be_vx)
CRC32_VX_FINUP(crc32c, crc32c_le_vx)

#घोषणा CRC32_VX_DIGEST(alg, func)					      \
	अटल पूर्णांक alg ## _vx_digest(काष्ठा shash_desc *desc, स्थिर u8 *data, \
				     अचिन्हित पूर्णांक len, u8 *out)		      \
	अणु								      \
		वापस __ ## alg ## _vx_finup(crypto_shash_ctx(desc->tfm),    \
					      data, len, out);		      \
	पूर्ण

CRC32_VX_DIGEST(crc32le, crc32_le_vx)
CRC32_VX_DIGEST(crc32be, crc32_be_vx)
CRC32_VX_DIGEST(crc32c, crc32c_le_vx)

#घोषणा CRC32_VX_UPDATE(alg, func)					      \
	अटल पूर्णांक alg ## _vx_update(काष्ठा shash_desc *desc, स्थिर u8 *data, \
				     अचिन्हित पूर्णांक datalen)		      \
	अणु								      \
		काष्ठा crc_desc_ctx *ctx = shash_desc_ctx(desc);	      \
		ctx->crc = func(ctx->crc, data, datalen);		      \
		वापस 0;						      \
	पूर्ण

CRC32_VX_UPDATE(crc32le, crc32_le_vx)
CRC32_VX_UPDATE(crc32be, crc32_be_vx)
CRC32_VX_UPDATE(crc32c, crc32c_le_vx)


अटल काष्ठा shash_alg crc32_vx_algs[] = अणु
	/* CRC-32 LE */
	अणु
		.init		=	crc32_vx_init,
		.setkey		=	crc32_vx_setkey,
		.update		=	crc32le_vx_update,
		.final		=	crc32le_vx_final,
		.finup		=	crc32le_vx_finup,
		.digest		=	crc32le_vx_digest,
		.descsize	=	माप(काष्ठा crc_desc_ctx),
		.digestsize	=	CRC32_DIGEST_SIZE,
		.base		=	अणु
			.cra_name	 = "crc32",
			.cra_driver_name = "crc32-vx",
			.cra_priority	 = 200,
			.cra_flags	 = CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize	 = CRC32_BLOCK_SIZE,
			.cra_ctxsize	 = माप(काष्ठा crc_ctx),
			.cra_module	 = THIS_MODULE,
			.cra_init	 = crc32_vx_cra_init_zero,
		पूर्ण,
	पूर्ण,
	/* CRC-32 BE */
	अणु
		.init		=	crc32_vx_init,
		.setkey		=	crc32be_vx_setkey,
		.update		=	crc32be_vx_update,
		.final		=	crc32be_vx_final,
		.finup		=	crc32be_vx_finup,
		.digest		=	crc32be_vx_digest,
		.descsize	=	माप(काष्ठा crc_desc_ctx),
		.digestsize	=	CRC32_DIGEST_SIZE,
		.base		=	अणु
			.cra_name	 = "crc32be",
			.cra_driver_name = "crc32be-vx",
			.cra_priority	 = 200,
			.cra_flags	 = CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize	 = CRC32_BLOCK_SIZE,
			.cra_ctxsize	 = माप(काष्ठा crc_ctx),
			.cra_module	 = THIS_MODULE,
			.cra_init	 = crc32_vx_cra_init_zero,
		पूर्ण,
	पूर्ण,
	/* CRC-32C LE */
	अणु
		.init		=	crc32_vx_init,
		.setkey		=	crc32_vx_setkey,
		.update		=	crc32c_vx_update,
		.final		=	crc32c_vx_final,
		.finup		=	crc32c_vx_finup,
		.digest		=	crc32c_vx_digest,
		.descsize	=	माप(काष्ठा crc_desc_ctx),
		.digestsize	=	CRC32_DIGEST_SIZE,
		.base		=	अणु
			.cra_name	 = "crc32c",
			.cra_driver_name = "crc32c-vx",
			.cra_priority	 = 200,
			.cra_flags	 = CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize	 = CRC32_BLOCK_SIZE,
			.cra_ctxsize	 = माप(काष्ठा crc_ctx),
			.cra_module	 = THIS_MODULE,
			.cra_init	 = crc32_vx_cra_init_invert,
		पूर्ण,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init crc_vx_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(crc32_vx_algs,
				       ARRAY_SIZE(crc32_vx_algs));
पूर्ण

अटल व्योम __निकास crc_vx_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(crc32_vx_algs, ARRAY_SIZE(crc32_vx_algs));
पूर्ण

module_cpu_feature_match(VXRS, crc_vx_mod_init);
module_निकास(crc_vx_mod_निकास);

MODULE_AUTHOR("Hendrik Brueckner <brueckner@linux.vnet.ibm.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS_CRYPTO("crc32");
MODULE_ALIAS_CRYPTO("crc32-vx");
MODULE_ALIAS_CRYPTO("crc32c");
MODULE_ALIAS_CRYPTO("crc32c-vx");
