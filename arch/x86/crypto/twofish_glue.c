<शैली गुरु>
/*
 * Glue Code क्रम assembler optimized version of TWOFISH
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
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 * USA
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

#समावेश <crypto/twofish.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

यंत्रlinkage व्योम twofish_enc_blk(काष्ठा twofish_ctx *ctx, u8 *dst,
				स्थिर u8 *src);
EXPORT_SYMBOL_GPL(twofish_enc_blk);
यंत्रlinkage व्योम twofish_dec_blk(काष्ठा twofish_ctx *ctx, u8 *dst,
				स्थिर u8 *src);
EXPORT_SYMBOL_GPL(twofish_dec_blk);

अटल व्योम twofish_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	twofish_enc_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल व्योम twofish_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	twofish_dec_blk(crypto_tfm_ctx(tfm), dst, src);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		=	"twofish",
	.cra_driver_name	=	"twofish-asm",
	.cra_priority		=	200,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	TF_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा twofish_ctx),
	.cra_alignmask		=	0,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	TF_MIN_KEY_SIZE,
			.cia_max_keysize	=	TF_MAX_KEY_SIZE,
			.cia_setkey		=	twofish_setkey,
			.cia_encrypt		=	twofish_encrypt,
			.cia_decrypt		=	twofish_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&alg);
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
पूर्ण

module_init(init);
module_निकास(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION ("Twofish Cipher Algorithm, asm optimized");
MODULE_ALIAS_CRYPTO("twofish");
MODULE_ALIAS_CRYPTO("twofish-asm");
