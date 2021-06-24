<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Twofish क्रम CryptoAPI
 *
 * Originally Twofish क्रम GPG
 * By Matthew Skala <mskala@ansuz.sooke.bc.ca>, July 26, 1998
 * 256-bit key length added March 20, 1999
 * Some modअगरications to reduce the text size by Werner Koch, April, 1998
 * Ported to the kerneli patch by Marc Mutz <Marc@Mutz.com>
 * Ported to CryptoAPI by Colin Slater <hoho@tacomeat.net>
 *
 * The original author has disclaimed all copyright पूर्णांकerest in this
 * code and thus put it in the खुला करोमुख्य. The subsequent authors 
 * have put this under the GNU General Public License.
 *
 * This code is a "clean room" implementation, written from the paper
 * _Twofish: A 128-Bit Block Cipher_ by Bruce Schneier, John Kअन्यथाy,
 * Doug Whiting, David Wagner, Chris Hall, and Niels Ferguson, available
 * through http://www.counterpane.com/twofish.hपंचांगl
 *
 * For background inक्रमmation on multiplication in finite fields, used क्रम
 * the matrix operations in the key schedule, see the book _Contemporary
 * Abstract Algebra_ by Joseph A. Gallian, especially chapter 22 in the
 * Third Edition.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/twofish.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crypto.h>
#समावेश <linux/bitops.h>

/* Macros to compute the g() function in the encryption and decryption
 * rounds.  G1 is the straight g() function; G2 includes the 8-bit
 * rotation क्रम the high 32-bit word. */

#घोषणा G1(a) \
     (ctx->s[0][(a) & 0xFF]) ^ (ctx->s[1][((a) >> 8) & 0xFF]) \
   ^ (ctx->s[2][((a) >> 16) & 0xFF]) ^ (ctx->s[3][(a) >> 24])

#घोषणा G2(b) \
     (ctx->s[1][(b) & 0xFF]) ^ (ctx->s[2][((b) >> 8) & 0xFF]) \
   ^ (ctx->s[3][((b) >> 16) & 0xFF]) ^ (ctx->s[0][(b) >> 24])

/* Encryption and decryption Feistel rounds.  Each one calls the two g()
 * macros, करोes the PHT, and perक्रमms the XOR and the appropriate bit
 * rotations.  The parameters are the round number (used to select subkeys),
 * and the four 32-bit chunks of the text. */

#घोषणा ENCROUND(n, a, b, c, d) \
   x = G1 (a); y = G2 (b); \
   x += y; y += x + ctx->k[2 * (n) + 1]; \
   (c) ^= x + ctx->k[2 * (n)]; \
   (c) = ror32((c), 1); \
   (d) = rol32((d), 1) ^ y

#घोषणा DECROUND(n, a, b, c, d) \
   x = G1 (a); y = G2 (b); \
   x += y; y += x; \
   (d) ^= y + ctx->k[2 * (n) + 1]; \
   (d) = ror32((d), 1); \
   (c) = rol32((c), 1); \
   (c) ^= (x + ctx->k[2 * (n)])

/* Encryption and decryption cycles; each one is simply two Feistel rounds
 * with the 32-bit chunks re-ordered to simulate the "swap" */

#घोषणा ENCCYCLE(n) \
   ENCROUND (2 * (n), a, b, c, d); \
   ENCROUND (2 * (n) + 1, c, d, a, b)

#घोषणा DECCYCLE(n) \
   DECROUND (2 * (n) + 1, c, d, a, b); \
   DECROUND (2 * (n), a, b, c, d)

/* Macros to convert the input and output bytes पूर्णांकo 32-bit words,
 * and simultaneously perक्रमm the whitening step.  INPACK packs word
 * number n पूर्णांकo the variable named by x, using whitening subkey number m.
 * OUTUNPACK unpacks word number n from the variable named by x, using
 * whitening subkey number m. */

#घोषणा INPACK(n, x, m) \
   x = get_unaligned_le32(in + (n) * 4) ^ ctx->w[m]

#घोषणा OUTUNPACK(n, x, m) \
   x ^= ctx->w[m]; \
   put_unaligned_le32(x, out + (n) * 4)



/* Encrypt one block.  in and out may be the same. */
अटल व्योम twofish_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा twofish_ctx *ctx = crypto_tfm_ctx(tfm);

	/* The four 32-bit chunks of the text. */
	u32 a, b, c, d;
	
	/* Temporaries used by the round function. */
	u32 x, y;

	/* Input whitening and packing. */
	INPACK (0, a, 0);
	INPACK (1, b, 1);
	INPACK (2, c, 2);
	INPACK (3, d, 3);
	
	/* Encryption Feistel cycles. */
	ENCCYCLE (0);
	ENCCYCLE (1);
	ENCCYCLE (2);
	ENCCYCLE (3);
	ENCCYCLE (4);
	ENCCYCLE (5);
	ENCCYCLE (6);
	ENCCYCLE (7);
	
	/* Output whitening and unpacking. */
	OUTUNPACK (0, c, 4);
	OUTUNPACK (1, d, 5);
	OUTUNPACK (2, a, 6);
	OUTUNPACK (3, b, 7);
	
पूर्ण

/* Decrypt one block.  in and out may be the same. */
अटल व्योम twofish_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा twofish_ctx *ctx = crypto_tfm_ctx(tfm);
  
	/* The four 32-bit chunks of the text. */
	u32 a, b, c, d;
	
	/* Temporaries used by the round function. */
	u32 x, y;
	
	/* Input whitening and packing. */
	INPACK (0, c, 4);
	INPACK (1, d, 5);
	INPACK (2, a, 6);
	INPACK (3, b, 7);
	
	/* Encryption Feistel cycles. */
	DECCYCLE (7);
	DECCYCLE (6);
	DECCYCLE (5);
	DECCYCLE (4);
	DECCYCLE (3);
	DECCYCLE (2);
	DECCYCLE (1);
	DECCYCLE (0);

	/* Output whitening and unpacking. */
	OUTUNPACK (0, a, 0);
	OUTUNPACK (1, b, 1);
	OUTUNPACK (2, c, 2);
	OUTUNPACK (3, d, 3);

पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name           =   "twofish",
	.cra_driver_name    =   "twofish-generic",
	.cra_priority       =   100,
	.cra_flags          =   CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize      =   TF_BLOCK_SIZE,
	.cra_ctxsize        =   माप(काष्ठा twofish_ctx),
	.cra_module         =   THIS_MODULE,
	.cra_u              =   अणु .cipher = अणु
	.cia_min_keysize    =   TF_MIN_KEY_SIZE,
	.cia_max_keysize    =   TF_MAX_KEY_SIZE,
	.cia_setkey         =   twofish_setkey,
	.cia_encrypt        =   twofish_encrypt,
	.cia_decrypt        =   twofish_decrypt पूर्ण पूर्ण
पूर्ण;

अटल पूर्णांक __init twofish_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&alg);
पूर्ण

अटल व्योम __निकास twofish_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
पूर्ण

subsys_initcall(twofish_mod_init);
module_निकास(twofish_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION ("Twofish Cipher Algorithm");
MODULE_ALIAS_CRYPTO("twofish");
MODULE_ALIAS_CRYPTO("twofish-generic");
