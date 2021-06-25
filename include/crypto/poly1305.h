<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम the Poly1305 algorithm
 */

#अगर_अघोषित _CRYPTO_POLY1305_H
#घोषणा _CRYPTO_POLY1305_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>

#घोषणा POLY1305_BLOCK_SIZE	16
#घोषणा POLY1305_KEY_SIZE	32
#घोषणा POLY1305_DIGEST_SIZE	16

/* The poly1305_key and poly1305_state types are mostly opaque and
 * implementation-defined. Limbs might be in base 2^64 or base 2^26, or
 * dअगरferent yet. The जोड़ type provided keeps these 64-bit aligned क्रम the
 * हाल in which this is implemented using 64x64 multiplies.
 */

काष्ठा poly1305_key अणु
	जोड़ अणु
		u32 r[5];
		u64 r64[3];
	पूर्ण;
पूर्ण;

काष्ठा poly1305_core_key अणु
	काष्ठा poly1305_key key;
	काष्ठा poly1305_key precomputed_s;
पूर्ण;

काष्ठा poly1305_state अणु
	जोड़ अणु
		u32 h[5];
		u64 h64[3];
	पूर्ण;
पूर्ण;

काष्ठा poly1305_desc_ctx अणु
	/* partial buffer */
	u8 buf[POLY1305_BLOCK_SIZE];
	/* bytes used in partial buffer */
	अचिन्हित पूर्णांक buflen;
	/* how many keys have been set in r[] */
	अचिन्हित लघु rset;
	/* whether s[] has been set */
	bool sset;
	/* finalize key */
	u32 s[4];
	/* accumulator */
	काष्ठा poly1305_state h;
	/* key */
	जोड़ अणु
		काष्ठा poly1305_key opaque_r[CONFIG_CRYPTO_LIB_POLY1305_RSIZE];
		काष्ठा poly1305_core_key core_r;
	पूर्ण;
पूर्ण;

व्योम poly1305_init_arch(काष्ठा poly1305_desc_ctx *desc,
			स्थिर u8 key[POLY1305_KEY_SIZE]);
व्योम poly1305_init_generic(काष्ठा poly1305_desc_ctx *desc,
			   स्थिर u8 key[POLY1305_KEY_SIZE]);

अटल अंतरभूत व्योम poly1305_init(काष्ठा poly1305_desc_ctx *desc, स्थिर u8 *key)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_POLY1305))
		poly1305_init_arch(desc, key);
	अन्यथा
		poly1305_init_generic(desc, key);
पूर्ण

व्योम poly1305_update_arch(काष्ठा poly1305_desc_ctx *desc, स्थिर u8 *src,
			  अचिन्हित पूर्णांक nbytes);
व्योम poly1305_update_generic(काष्ठा poly1305_desc_ctx *desc, स्थिर u8 *src,
			     अचिन्हित पूर्णांक nbytes);

अटल अंतरभूत व्योम poly1305_update(काष्ठा poly1305_desc_ctx *desc,
				   स्थिर u8 *src, अचिन्हित पूर्णांक nbytes)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_POLY1305))
		poly1305_update_arch(desc, src, nbytes);
	अन्यथा
		poly1305_update_generic(desc, src, nbytes);
पूर्ण

व्योम poly1305_final_arch(काष्ठा poly1305_desc_ctx *desc, u8 *digest);
व्योम poly1305_final_generic(काष्ठा poly1305_desc_ctx *desc, u8 *digest);

अटल अंतरभूत व्योम poly1305_final(काष्ठा poly1305_desc_ctx *desc, u8 *digest)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_POLY1305))
		poly1305_final_arch(desc, digest);
	अन्यथा
		poly1305_final_generic(desc, digest);
पूर्ण

#पूर्ण_अगर
