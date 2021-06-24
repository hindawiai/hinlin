<शैली गुरु>
/*
 * Cryptographic API.
 *
 * T10 Data Integrity Field CRC16 Crypto Transक्रमm
 *
 * Copyright (c) 2007 Oracle Corporation.  All rights reserved.
 * Written by Martin K. Petersen <martin.petersen@oracle.com>
 * Copyright (C) 2013 Intel Corporation
 * Author: Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

काष्ठा chksum_desc_ctx अणु
	__u16 crc;
पूर्ण;

/*
 * Steps through buffer one byte at a समय, calculates reflected
 * crc using table.
 */

अटल पूर्णांक chksum_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक chksum_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->crc = crc_t10dअगर_generic(ctx->crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__u16 *)out = ctx->crc;
	वापस 0;
पूर्ण

अटल पूर्णांक __chksum_finup(__u16 crc, स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out)
अणु
	*(__u16 *)out = crc_t10dअगर_generic(crc, data, len);
	वापस 0;
पूर्ण

अटल पूर्णांक chksum_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	वापस __chksum_finup(ctx->crc, data, len, out);
पूर्ण

अटल पूर्णांक chksum_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length, u8 *out)
अणु
	वापस __chksum_finup(0, data, length, out);
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize		=	CRC_T10DIF_DIGEST_SIZE,
	.init		=	chksum_init,
	.update		=	chksum_update,
	.final		=	chksum_final,
	.finup		=	chksum_finup,
	.digest		=	chksum_digest,
	.descsize		=	माप(काष्ठा chksum_desc_ctx),
	.base			=	अणु
		.cra_name		=	"crct10dif",
		.cra_driver_name	=	"crct10dif-generic",
		.cra_priority		=	100,
		.cra_blocksize		=	CRC_T10DIF_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crct10dअगर_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crct10dअगर_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(crct10dअगर_mod_init);
module_निकास(crct10dअगर_mod_fini);

MODULE_AUTHOR("Tim Chen <tim.c.chen@linux.intel.com>");
MODULE_DESCRIPTION("T10 DIF CRC calculation.");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("crct10dif");
MODULE_ALIAS_CRYPTO("crct10dif-generic");
