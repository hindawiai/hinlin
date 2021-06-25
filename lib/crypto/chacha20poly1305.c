<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the ChaCha20Poly1305 AEAD स्थिरruction.
 *
 * Inक्रमmation: https://tools.ietf.org/hपंचांगl/rfc8439
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/chacha20poly1305.h>
#समावेश <crypto/chacha.h>
#समावेश <crypto/poly1305.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#घोषणा CHACHA_KEY_WORDS	(CHACHA_KEY_SIZE / माप(u32))

अटल व्योम chacha_load_key(u32 *k, स्थिर u8 *in)
अणु
	k[0] = get_unaligned_le32(in);
	k[1] = get_unaligned_le32(in + 4);
	k[2] = get_unaligned_le32(in + 8);
	k[3] = get_unaligned_le32(in + 12);
	k[4] = get_unaligned_le32(in + 16);
	k[5] = get_unaligned_le32(in + 20);
	k[6] = get_unaligned_le32(in + 24);
	k[7] = get_unaligned_le32(in + 28);
पूर्ण

अटल व्योम xchacha_init(u32 *chacha_state, स्थिर u8 *key, स्थिर u8 *nonce)
अणु
	u32 k[CHACHA_KEY_WORDS];
	u8 iv[CHACHA_IV_SIZE];

	स_रखो(iv, 0, 8);
	स_नकल(iv + 8, nonce + 16, 8);

	chacha_load_key(k, key);

	/* Compute the subkey given the original key and first 128 nonce bits */
	chacha_init(chacha_state, k, nonce);
	hchacha_block(chacha_state, k, 20);

	chacha_init(chacha_state, k, iv);

	memzero_explicit(k, माप(k));
	memzero_explicit(iv, माप(iv));
पूर्ण

अटल व्योम
__chacha20poly1305_encrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			   स्थिर u8 *ad, स्थिर माप_प्रकार ad_len, u32 *chacha_state)
अणु
	स्थिर u8 *pad0 = page_address(ZERO_PAGE(0));
	काष्ठा poly1305_desc_ctx poly1305_state;
	जोड़ अणु
		u8 block0[POLY1305_KEY_SIZE];
		__le64 lens[2];
	पूर्ण b;

	chacha20_crypt(chacha_state, b.block0, pad0, माप(b.block0));
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len);
	अगर (ad_len & 0xf)
		poly1305_update(&poly1305_state, pad0, 0x10 - (ad_len & 0xf));

	chacha20_crypt(chacha_state, dst, src, src_len);

	poly1305_update(&poly1305_state, dst, src_len);
	अगर (src_len & 0xf)
		poly1305_update(&poly1305_state, pad0, 0x10 - (src_len & 0xf));

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(src_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, माप(b.lens));

	poly1305_final(&poly1305_state, dst + src_len);

	memzero_explicit(chacha_state, CHACHA_STATE_WORDS * माप(u32));
	memzero_explicit(&b, माप(b));
पूर्ण

व्योम chacha20poly1305_encrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			      स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			      स्थिर u64 nonce,
			      स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	u32 chacha_state[CHACHA_STATE_WORDS];
	u32 k[CHACHA_KEY_WORDS];
	__le64 iv[2];

	chacha_load_key(k, key);

	iv[0] = 0;
	iv[1] = cpu_to_le64(nonce);

	chacha_init(chacha_state, k, (u8 *)iv);
	__chacha20poly1305_encrypt(dst, src, src_len, ad, ad_len, chacha_state);

	memzero_explicit(iv, माप(iv));
	memzero_explicit(k, माप(k));
पूर्ण
EXPORT_SYMBOL(chacha20poly1305_encrypt);

व्योम xchacha20poly1305_encrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			       स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			       स्थिर u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
			       स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	u32 chacha_state[CHACHA_STATE_WORDS];

	xchacha_init(chacha_state, key, nonce);
	__chacha20poly1305_encrypt(dst, src, src_len, ad, ad_len, chacha_state);
पूर्ण
EXPORT_SYMBOL(xchacha20poly1305_encrypt);

अटल bool
__chacha20poly1305_decrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			   स्थिर u8 *ad, स्थिर माप_प्रकार ad_len, u32 *chacha_state)
अणु
	स्थिर u8 *pad0 = page_address(ZERO_PAGE(0));
	काष्ठा poly1305_desc_ctx poly1305_state;
	माप_प्रकार dst_len;
	पूर्णांक ret;
	जोड़ अणु
		u8 block0[POLY1305_KEY_SIZE];
		u8 mac[POLY1305_DIGEST_SIZE];
		__le64 lens[2];
	पूर्ण b;

	अगर (unlikely(src_len < POLY1305_DIGEST_SIZE))
		वापस false;

	chacha20_crypt(chacha_state, b.block0, pad0, माप(b.block0));
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len);
	अगर (ad_len & 0xf)
		poly1305_update(&poly1305_state, pad0, 0x10 - (ad_len & 0xf));

	dst_len = src_len - POLY1305_DIGEST_SIZE;
	poly1305_update(&poly1305_state, src, dst_len);
	अगर (dst_len & 0xf)
		poly1305_update(&poly1305_state, pad0, 0x10 - (dst_len & 0xf));

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(dst_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, माप(b.lens));

	poly1305_final(&poly1305_state, b.mac);

	ret = crypto_memneq(b.mac, src + dst_len, POLY1305_DIGEST_SIZE);
	अगर (likely(!ret))
		chacha20_crypt(chacha_state, dst, src, dst_len);

	memzero_explicit(&b, माप(b));

	वापस !ret;
पूर्ण

bool chacha20poly1305_decrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			      स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			      स्थिर u64 nonce,
			      स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	u32 chacha_state[CHACHA_STATE_WORDS];
	u32 k[CHACHA_KEY_WORDS];
	__le64 iv[2];
	bool ret;

	chacha_load_key(k, key);

	iv[0] = 0;
	iv[1] = cpu_to_le64(nonce);

	chacha_init(chacha_state, k, (u8 *)iv);
	ret = __chacha20poly1305_decrypt(dst, src, src_len, ad, ad_len,
					 chacha_state);

	memzero_explicit(chacha_state, माप(chacha_state));
	memzero_explicit(iv, माप(iv));
	memzero_explicit(k, माप(k));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(chacha20poly1305_decrypt);

bool xchacha20poly1305_decrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			       स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			       स्थिर u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
			       स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	u32 chacha_state[CHACHA_STATE_WORDS];

	xchacha_init(chacha_state, key, nonce);
	वापस __chacha20poly1305_decrypt(dst, src, src_len, ad, ad_len,
					  chacha_state);
पूर्ण
EXPORT_SYMBOL(xchacha20poly1305_decrypt);

अटल
bool chacha20poly1305_crypt_sg_inplace(काष्ठा scatterlist *src,
				       स्थिर माप_प्रकार src_len,
				       स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
				       स्थिर u64 nonce,
				       स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE],
				       पूर्णांक encrypt)
अणु
	स्थिर u8 *pad0 = page_address(ZERO_PAGE(0));
	काष्ठा poly1305_desc_ctx poly1305_state;
	u32 chacha_state[CHACHA_STATE_WORDS];
	काष्ठा sg_mapping_iter miter;
	माप_प्रकार partial = 0;
	अचिन्हित पूर्णांक flags;
	bool ret = true;
	पूर्णांक sl;
	जोड़ अणु
		काष्ठा अणु
			u32 k[CHACHA_KEY_WORDS];
			__le64 iv[2];
		पूर्ण;
		u8 block0[POLY1305_KEY_SIZE];
		u8 chacha_stream[CHACHA_BLOCK_SIZE];
		काष्ठा अणु
			u8 mac[2][POLY1305_DIGEST_SIZE];
		पूर्ण;
		__le64 lens[2];
	पूर्ण b __aligned(16);

	अगर (WARN_ON(src_len > पूर्णांक_उच्च))
		वापस false;

	chacha_load_key(b.k, key);

	b.iv[0] = 0;
	b.iv[1] = cpu_to_le64(nonce);

	chacha_init(chacha_state, b.k, (u8 *)b.iv);
	chacha20_crypt(chacha_state, b.block0, pad0, माप(b.block0));
	poly1305_init(&poly1305_state, b.block0);

	अगर (unlikely(ad_len)) अणु
		poly1305_update(&poly1305_state, ad, ad_len);
		अगर (ad_len & 0xf)
			poly1305_update(&poly1305_state, pad0, 0x10 - (ad_len & 0xf));
	पूर्ण

	flags = SG_MITER_TO_SG | SG_MITER_ATOMIC;

	sg_miter_start(&miter, src, sg_nents(src), flags);

	क्रम (sl = src_len; sl > 0 && sg_miter_next(&miter); sl -= miter.length) अणु
		u8 *addr = miter.addr;
		माप_प्रकार length = min_t(माप_प्रकार, sl, miter.length);

		अगर (!encrypt)
			poly1305_update(&poly1305_state, addr, length);

		अगर (unlikely(partial)) अणु
			माप_प्रकार l = min(length, CHACHA_BLOCK_SIZE - partial);

			crypto_xor(addr, b.chacha_stream + partial, l);
			partial = (partial + l) & (CHACHA_BLOCK_SIZE - 1);

			addr += l;
			length -= l;
		पूर्ण

		अगर (likely(length >= CHACHA_BLOCK_SIZE || length == sl)) अणु
			माप_प्रकार l = length;

			अगर (unlikely(length < sl))
				l &= ~(CHACHA_BLOCK_SIZE - 1);
			chacha20_crypt(chacha_state, addr, addr, l);
			addr += l;
			length -= l;
		पूर्ण

		अगर (unlikely(length > 0)) अणु
			chacha20_crypt(chacha_state, b.chacha_stream, pad0,
				       CHACHA_BLOCK_SIZE);
			crypto_xor(addr, b.chacha_stream, length);
			partial = length;
		पूर्ण

		अगर (encrypt)
			poly1305_update(&poly1305_state, miter.addr,
					min_t(माप_प्रकार, sl, miter.length));
	पूर्ण

	अगर (src_len & 0xf)
		poly1305_update(&poly1305_state, pad0, 0x10 - (src_len & 0xf));

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(src_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, माप(b.lens));

	अगर (likely(sl <= -POLY1305_DIGEST_SIZE)) अणु
		अगर (encrypt) अणु
			poly1305_final(&poly1305_state,
				       miter.addr + miter.length + sl);
			ret = true;
		पूर्ण अन्यथा अणु
			poly1305_final(&poly1305_state, b.mac[0]);
			ret = !crypto_memneq(b.mac[0],
					     miter.addr + miter.length + sl,
					     POLY1305_DIGEST_SIZE);
		पूर्ण
	पूर्ण

	sg_miter_stop(&miter);

	अगर (unlikely(sl > -POLY1305_DIGEST_SIZE)) अणु
		poly1305_final(&poly1305_state, b.mac[1]);
		scatterwalk_map_and_copy(b.mac[encrypt], src, src_len,
					 माप(b.mac[1]), encrypt);
		ret = encrypt ||
		      !crypto_memneq(b.mac[0], b.mac[1], POLY1305_DIGEST_SIZE);
	पूर्ण

	memzero_explicit(chacha_state, माप(chacha_state));
	memzero_explicit(&b, माप(b));

	वापस ret;
पूर्ण

bool chacha20poly1305_encrypt_sg_inplace(काष्ठा scatterlist *src, माप_प्रकार src_len,
					 स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
					 स्थिर u64 nonce,
					 स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	वापस chacha20poly1305_crypt_sg_inplace(src, src_len, ad, ad_len,
						 nonce, key, 1);
पूर्ण
EXPORT_SYMBOL(chacha20poly1305_encrypt_sg_inplace);

bool chacha20poly1305_decrypt_sg_inplace(काष्ठा scatterlist *src, माप_प्रकार src_len,
					 स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
					 स्थिर u64 nonce,
					 स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE])
अणु
	अगर (unlikely(src_len < POLY1305_DIGEST_SIZE))
		वापस false;

	वापस chacha20poly1305_crypt_sg_inplace(src,
						 src_len - POLY1305_DIGEST_SIZE,
						 ad, ad_len, nonce, key, 0);
पूर्ण
EXPORT_SYMBOL(chacha20poly1305_decrypt_sg_inplace);

अटल पूर्णांक __init mod_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_CRYPTO_MANAGER_DISABLE_TESTS) &&
	    WARN_ON(!chacha20poly1305_selftest()))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChaCha20Poly1305 AEAD construction");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
