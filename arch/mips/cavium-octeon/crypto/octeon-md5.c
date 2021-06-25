<शैली गुरु>
/*
 * Cryptographic API.
 *
 * MD5 Message Digest Algorithm (RFC1321).
 *
 * Adapted क्रम OCTEON by Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 * Based on crypto/md5.c, which is:
 *
 * Derived from cryptoapi implementation, originally based on the
 * खुला करोमुख्य implementation written by Colin Plumb in 1993.
 *
 * Copyright (c) Cryptoapi developers.
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश <crypto/md5.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/octeon/octeon.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "octeon-crypto.h"

/*
 * We pass everything as 64-bit. OCTEON can handle misaligned data.
 */

अटल व्योम octeon_md5_store_hash(काष्ठा md5_state *ctx)
अणु
	u64 *hash = (u64 *)ctx->hash;

	ग_लिखो_octeon_64bit_hash_dword(hash[0], 0);
	ग_लिखो_octeon_64bit_hash_dword(hash[1], 1);
पूर्ण

अटल व्योम octeon_md5_पढ़ो_hash(काष्ठा md5_state *ctx)
अणु
	u64 *hash = (u64 *)ctx->hash;

	hash[0] = पढ़ो_octeon_64bit_hash_dword(0);
	hash[1] = पढ़ो_octeon_64bit_hash_dword(1);
पूर्ण

अटल व्योम octeon_md5_transक्रमm(स्थिर व्योम *_block)
अणु
	स्थिर u64 *block = _block;

	ग_लिखो_octeon_64bit_block_dword(block[0], 0);
	ग_लिखो_octeon_64bit_block_dword(block[1], 1);
	ग_लिखो_octeon_64bit_block_dword(block[2], 2);
	ग_लिखो_octeon_64bit_block_dword(block[3], 3);
	ग_लिखो_octeon_64bit_block_dword(block[4], 4);
	ग_लिखो_octeon_64bit_block_dword(block[5], 5);
	ग_लिखो_octeon_64bit_block_dword(block[6], 6);
	octeon_md5_start(block[7]);
पूर्ण

अटल पूर्णांक octeon_md5_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	cpu_to_le32_array(mctx->hash, 4);
	mctx->byte_count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_md5_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);
	स्थिर u32 avail = माप(mctx->block) - (mctx->byte_count & 0x3f);
	काष्ठा octeon_cop2_state state;
	अचिन्हित दीर्घ flags;

	mctx->byte_count += len;

	अगर (avail > len) अणु
		स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
		       data, len);
		वापस 0;
	पूर्ण

	स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail), data,
	       avail);

	flags = octeon_crypto_enable(&state);
	octeon_md5_store_hash(mctx);

	octeon_md5_transक्रमm(mctx->block);
	data += avail;
	len -= avail;

	जबतक (len >= माप(mctx->block)) अणु
		octeon_md5_transक्रमm(data);
		data += माप(mctx->block);
		len -= माप(mctx->block);
	पूर्ण

	octeon_md5_पढ़ो_hash(mctx);
	octeon_crypto_disable(&state, flags);

	स_नकल(mctx->block, data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_md5_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = mctx->byte_count & 0x3f;
	अक्षर *p = (अक्षर *)mctx->block + offset;
	पूर्णांक padding = 56 - (offset + 1);
	काष्ठा octeon_cop2_state state;
	अचिन्हित दीर्घ flags;

	*p++ = 0x80;

	flags = octeon_crypto_enable(&state);
	octeon_md5_store_hash(mctx);

	अगर (padding < 0) अणु
		स_रखो(p, 0x00, padding + माप(u64));
		octeon_md5_transक्रमm(mctx->block);
		p = (अक्षर *)mctx->block;
		padding = 56;
	पूर्ण

	स_रखो(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	cpu_to_le32_array(mctx->block + 14, 2);
	octeon_md5_transक्रमm(mctx->block);

	octeon_md5_पढ़ो_hash(mctx);
	octeon_crypto_disable(&state, flags);

	स_नकल(out, mctx->hash, माप(mctx->hash));
	स_रखो(mctx, 0, माप(*mctx));

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_md5_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा md5_state *ctx = shash_desc_ctx(desc);

	स_नकल(out, ctx, माप(*ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_md5_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा md5_state *ctx = shash_desc_ctx(desc);

	स_नकल(ctx, in, माप(*ctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	octeon_md5_init,
	.update		=	octeon_md5_update,
	.final		=	octeon_md5_final,
	.export		=	octeon_md5_export,
	.import		=	octeon_md5_import,
	.descsize	=	माप(काष्ठा md5_state),
	.statesize	=	माप(काष्ठा md5_state),
	.base		=	अणु
		.cra_name	=	"md5",
		.cra_driver_name=	"octeon-md5",
		.cra_priority	=	OCTEON_CR_OPCODE_PRIORITY,
		.cra_blocksize	=	MD5_HMAC_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init md5_mod_init(व्योम)
अणु
	अगर (!octeon_has_crypto())
		वापस -ENOTSUPP;
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास md5_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(md5_mod_init);
module_निकास(md5_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD5 Message Digest Algorithm (OCTEON)");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
