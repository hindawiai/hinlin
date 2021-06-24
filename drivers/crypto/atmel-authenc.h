<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * API क्रम Aपंचांगel Secure Protocol Layers Improved Perक्रमmances (SPLIP)
 *
 * Copyright (C) 2016 Aपंचांगel Corporation
 *
 * Author: Cyrille Pitchen <cyrille.pitchen@aपंचांगel.com>
 *
 * This driver is based on drivers/mtd/spi-nor/fsl-quadspi.c from Freescale.
 */

#अगर_अघोषित __ATMEL_AUTHENC_H__
#घोषणा __ATMEL_AUTHENC_H__

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)

#समावेश <crypto/authenc.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश "atmel-sha-regs.h"

काष्ठा aपंचांगel_aes_dev;
प्रकार पूर्णांक (*aपंचांगel_aes_authenc_fn_t)(काष्ठा aपंचांगel_aes_dev *, पूर्णांक, bool);

काष्ठा aपंचांगel_sha_authenc_ctx;

bool aपंचांगel_sha_authenc_is_पढ़ोy(व्योम);
अचिन्हित पूर्णांक aपंचांगel_sha_authenc_get_reqsize(व्योम);

काष्ठा aपंचांगel_sha_authenc_ctx *aपंचांगel_sha_authenc_spawn(अचिन्हित दीर्घ mode);
व्योम aपंचांगel_sha_authenc_मुक्त(काष्ठा aपंचांगel_sha_authenc_ctx *auth);
पूर्णांक aपंचांगel_sha_authenc_setkey(काष्ठा aपंचांगel_sha_authenc_ctx *auth,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen, u32 flags);

पूर्णांक aपंचांगel_sha_authenc_schedule(काष्ठा ahash_request *req,
			       काष्ठा aपंचांगel_sha_authenc_ctx *auth,
			       aपंचांगel_aes_authenc_fn_t cb,
			       काष्ठा aपंचांगel_aes_dev *dd);
पूर्णांक aपंचांगel_sha_authenc_init(काष्ठा ahash_request *req,
			   काष्ठा scatterlist *assoc, अचिन्हित पूर्णांक assoclen,
			   अचिन्हित पूर्णांक textlen,
			   aपंचांगel_aes_authenc_fn_t cb,
			   काष्ठा aपंचांगel_aes_dev *dd);
पूर्णांक aपंचांगel_sha_authenc_final(काष्ठा ahash_request *req,
			    u32 *digest, अचिन्हित पूर्णांक digestlen,
			    aपंचांगel_aes_authenc_fn_t cb,
			    काष्ठा aपंचांगel_aes_dev *dd);
व्योम  aपंचांगel_sha_authenc_पात(काष्ठा ahash_request *req);

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_ATMEL_AUTHENC */

#पूर्ण_अगर /* __ATMEL_AUTHENC_H__ */
