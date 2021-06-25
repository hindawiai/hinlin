<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Compression operations.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 */
#समावेश <linux/crypto.h>
#समावेश "internal.h"

पूर्णांक crypto_comp_compress(काष्ठा crypto_comp *comp,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_comp_tfm(comp);

	वापस tfm->__crt_alg->cra_compress.coa_compress(tfm, src, slen, dst,
	                                                 dlen);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_comp_compress);

पूर्णांक crypto_comp_decompress(काष्ठा crypto_comp *comp,
			   स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			   u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_comp_tfm(comp);

	वापस tfm->__crt_alg->cra_compress.coa_decompress(tfm, src, slen, dst,
	                                                   dlen);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_comp_decompress);
