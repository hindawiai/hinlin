<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 generic implementation of the SHA Secure Hash Algorithms.
 *
 * Copyright IBM Corp. 2007
 * Author(s): Jan Glauber (jang@de.ibm.com)
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cpacf.h>
#समावेश "sha.h"

पूर्णांक s390_sha_update(काष्ठा shash_desc *desc, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा s390_sha_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक bsize = crypto_shash_blocksize(desc->tfm);
	अचिन्हित पूर्णांक index, n;

	/* how much is alपढ़ोy in the buffer? */
	index = ctx->count % bsize;
	ctx->count += len;

	अगर ((index + len) < bsize)
		जाओ store;

	/* process one stored block */
	अगर (index) अणु
		स_नकल(ctx->buf + index, data, bsize - index);
		cpacf_kimd(ctx->func, ctx->state, ctx->buf, bsize);
		data += bsize - index;
		len -= bsize - index;
		index = 0;
	पूर्ण

	/* process as many blocks as possible */
	अगर (len >= bsize) अणु
		n = (len / bsize) * bsize;
		cpacf_kimd(ctx->func, ctx->state, data, n);
		data += n;
		len -= n;
	पूर्ण
store:
	अगर (len)
		स_नकल(ctx->buf + index , data, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s390_sha_update);

अटल पूर्णांक s390_crypto_shash_parmsize(पूर्णांक func)
अणु
	चयन (func) अणु
	हाल CPACF_KLMD_SHA_1:
		वापस 20;
	हाल CPACF_KLMD_SHA_256:
		वापस 32;
	हाल CPACF_KLMD_SHA_512:
		वापस 64;
	हाल CPACF_KLMD_SHA3_224:
	हाल CPACF_KLMD_SHA3_256:
	हाल CPACF_KLMD_SHA3_384:
	हाल CPACF_KLMD_SHA3_512:
		वापस 200;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक s390_sha_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा s390_sha_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक bsize = crypto_shash_blocksize(desc->tfm);
	u64 bits;
	अचिन्हित पूर्णांक n;
	पूर्णांक mbl_offset;

	n = ctx->count % bsize;
	bits = ctx->count * 8;
	mbl_offset = s390_crypto_shash_parmsize(ctx->func);
	अगर (mbl_offset < 0)
		वापस -EINVAL;

	mbl_offset = mbl_offset / माप(u32);

	/* set total msg bit length (mbl) in CPACF parmblock */
	चयन (ctx->func) अणु
	हाल CPACF_KLMD_SHA_1:
	हाल CPACF_KLMD_SHA_256:
		स_नकल(ctx->state + mbl_offset, &bits, माप(bits));
		अवरोध;
	हाल CPACF_KLMD_SHA_512:
		/*
		 * the SHA512 parmblock has a 128-bit mbl field, clear
		 * high-order u64 field, copy bits to low-order u64 field
		 */
		स_रखो(ctx->state + mbl_offset, 0x00, माप(bits));
		mbl_offset += माप(u64) / माप(u32);
		स_नकल(ctx->state + mbl_offset, &bits, माप(bits));
		अवरोध;
	हाल CPACF_KLMD_SHA3_224:
	हाल CPACF_KLMD_SHA3_256:
	हाल CPACF_KLMD_SHA3_384:
	हाल CPACF_KLMD_SHA3_512:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cpacf_klmd(ctx->func, ctx->state, ctx->buf, n);

	/* copy digest to out */
	स_नकल(out, ctx->state, crypto_shash_digestsize(desc->tfm));
	/* wipe context */
	स_रखो(ctx, 0, माप *ctx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s390_sha_final);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("s390 SHA cipher common functions");
