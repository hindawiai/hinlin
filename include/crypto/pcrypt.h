<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pcrypt - Parallel crypto engine.
 *
 * Copyright (C) 2009 secunet Security Networks AG
 * Copyright (C) 2009 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#अगर_अघोषित _CRYPTO_PCRYPT_H
#घोषणा _CRYPTO_PCRYPT_H

#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/padata.h>

काष्ठा pcrypt_request अणु
	काष्ठा padata_priv	padata;
	व्योम			*data;
	व्योम			*__ctx[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

अटल अंतरभूत व्योम *pcrypt_request_ctx(काष्ठा pcrypt_request *req)
अणु
	वापस req->__ctx;
पूर्ण

अटल अंतरभूत
काष्ठा padata_priv *pcrypt_request_padata(काष्ठा pcrypt_request *req)
अणु
	वापस &req->padata;
पूर्ण

अटल अंतरभूत
काष्ठा pcrypt_request *pcrypt_padata_request(काष्ठा padata_priv *padata)
अणु
	वापस container_of(padata, काष्ठा pcrypt_request, padata);
पूर्ण

#पूर्ण_अगर
