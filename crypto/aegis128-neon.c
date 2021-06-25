<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/neon.h>

#समावेश "aegis.h"

व्योम crypto_aegis128_init_neon(व्योम *state, स्थिर व्योम *key, स्थिर व्योम *iv);
व्योम crypto_aegis128_update_neon(व्योम *state, स्थिर व्योम *msg);
व्योम crypto_aegis128_encrypt_chunk_neon(व्योम *state, व्योम *dst, स्थिर व्योम *src,
					अचिन्हित पूर्णांक size);
व्योम crypto_aegis128_decrypt_chunk_neon(व्योम *state, व्योम *dst, स्थिर व्योम *src,
					अचिन्हित पूर्णांक size);
पूर्णांक crypto_aegis128_final_neon(व्योम *state, व्योम *tag_xor,
			       अचिन्हित पूर्णांक assoclen,
			       अचिन्हित पूर्णांक cryptlen,
			       अचिन्हित पूर्णांक authsize);

पूर्णांक aegis128_have_aes_insn __ro_after_init;

bool crypto_aegis128_have_simd(व्योम)
अणु
	अगर (cpu_have_feature(cpu_feature(AES))) अणु
		aegis128_have_aes_insn = 1;
		वापस true;
	पूर्ण
	वापस IS_ENABLED(CONFIG_ARM64);
पूर्ण

व्योम crypto_aegis128_init_simd(काष्ठा aegis_state *state,
			       स्थिर जोड़ aegis_block *key,
			       स्थिर u8 *iv)
अणु
	kernel_neon_begin();
	crypto_aegis128_init_neon(state, key, iv);
	kernel_neon_end();
पूर्ण

व्योम crypto_aegis128_update_simd(काष्ठा aegis_state *state, स्थिर व्योम *msg)
अणु
	kernel_neon_begin();
	crypto_aegis128_update_neon(state, msg);
	kernel_neon_end();
पूर्ण

व्योम crypto_aegis128_encrypt_chunk_simd(काष्ठा aegis_state *state, u8 *dst,
					स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	kernel_neon_begin();
	crypto_aegis128_encrypt_chunk_neon(state, dst, src, size);
	kernel_neon_end();
पूर्ण

व्योम crypto_aegis128_decrypt_chunk_simd(काष्ठा aegis_state *state, u8 *dst,
					स्थिर u8 *src, अचिन्हित पूर्णांक size)
अणु
	kernel_neon_begin();
	crypto_aegis128_decrypt_chunk_neon(state, dst, src, size);
	kernel_neon_end();
पूर्ण

पूर्णांक crypto_aegis128_final_simd(काष्ठा aegis_state *state,
			       जोड़ aegis_block *tag_xor,
			       अचिन्हित पूर्णांक assoclen,
			       अचिन्हित पूर्णांक cryptlen,
			       अचिन्हित पूर्णांक authsize)
अणु
	पूर्णांक ret;

	kernel_neon_begin();
	ret = crypto_aegis128_final_neon(state, tag_xor, assoclen, cryptlen,
					 authsize);
	kernel_neon_end();

	वापस ret;
पूर्ण
