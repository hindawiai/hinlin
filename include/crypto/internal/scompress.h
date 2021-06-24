<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Synchronous Compression operations
 *
 * Copyright 2015 LG Electronics Inc.
 * Copyright (c) 2016, Intel Corporation
 * Author: Giovanni Cabiddu <giovanni.cabiddu@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_SCOMP_INT_H
#घोषणा _CRYPTO_SCOMP_INT_H
#समावेश <linux/crypto.h>

#घोषणा SCOMP_SCRATCH_SIZE	131072

काष्ठा crypto_scomp अणु
	काष्ठा crypto_tfm base;
पूर्ण;

/**
 * काष्ठा scomp_alg - synchronous compression algorithm
 *
 * @alloc_ctx:	Function allocates algorithm specअगरic context
 * @मुक्त_ctx:	Function मुक्तs context allocated with alloc_ctx
 * @compress:	Function perक्रमms a compress operation
 * @decompress:	Function perक्रमms a de-compress operation
 * @base:	Common crypto API algorithm data काष्ठाure
 */
काष्ठा scomp_alg अणु
	व्योम *(*alloc_ctx)(काष्ठा crypto_scomp *tfm);
	व्योम (*मुक्त_ctx)(काष्ठा crypto_scomp *tfm, व्योम *ctx);
	पूर्णांक (*compress)(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			व्योम *ctx);
	पूर्णांक (*decompress)(काष्ठा crypto_scomp *tfm, स्थिर u8 *src,
			  अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen,
			  व्योम *ctx);
	काष्ठा crypto_alg base;
पूर्ण;

अटल अंतरभूत काष्ठा scomp_alg *__crypto_scomp_alg(काष्ठा crypto_alg *alg)
अणु
	वापस container_of(alg, काष्ठा scomp_alg, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_scomp *__crypto_scomp_tfm(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm, काष्ठा crypto_scomp, base);
पूर्ण

अटल अंतरभूत काष्ठा crypto_tfm *crypto_scomp_tfm(काष्ठा crypto_scomp *tfm)
अणु
	वापस &tfm->base;
पूर्ण

अटल अंतरभूत व्योम crypto_मुक्त_scomp(काष्ठा crypto_scomp *tfm)
अणु
	crypto_destroy_tfm(tfm, crypto_scomp_tfm(tfm));
पूर्ण

अटल अंतरभूत काष्ठा scomp_alg *crypto_scomp_alg(काष्ठा crypto_scomp *tfm)
अणु
	वापस __crypto_scomp_alg(crypto_scomp_tfm(tfm)->__crt_alg);
पूर्ण

अटल अंतरभूत व्योम *crypto_scomp_alloc_ctx(काष्ठा crypto_scomp *tfm)
अणु
	वापस crypto_scomp_alg(tfm)->alloc_ctx(tfm);
पूर्ण

अटल अंतरभूत व्योम crypto_scomp_मुक्त_ctx(काष्ठा crypto_scomp *tfm,
					 व्योम *ctx)
अणु
	वापस crypto_scomp_alg(tfm)->मुक्त_ctx(tfm, ctx);
पूर्ण

अटल अंतरभूत पूर्णांक crypto_scomp_compress(काष्ठा crypto_scomp *tfm,
					स्थिर u8 *src, अचिन्हित पूर्णांक slen,
					u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	वापस crypto_scomp_alg(tfm)->compress(tfm, src, slen, dst, dlen, ctx);
पूर्ण

अटल अंतरभूत पूर्णांक crypto_scomp_decompress(काष्ठा crypto_scomp *tfm,
					  स्थिर u8 *src, अचिन्हित पूर्णांक slen,
					  u8 *dst, अचिन्हित पूर्णांक *dlen,
					  व्योम *ctx)
अणु
	वापस crypto_scomp_alg(tfm)->decompress(tfm, src, slen, dst, dlen,
						 ctx);
पूर्ण

पूर्णांक crypto_init_scomp_ops_async(काष्ठा crypto_tfm *tfm);
काष्ठा acomp_req *crypto_acomp_scomp_alloc_ctx(काष्ठा acomp_req *req);
व्योम crypto_acomp_scomp_मुक्त_ctx(काष्ठा acomp_req *req);

/**
 * crypto_रेजिस्टर_scomp() -- Register synchronous compression algorithm
 *
 * Function रेजिस्टरs an implementation of a synchronous
 * compression algorithm
 *
 * @alg:	algorithm definition
 *
 * Return: zero on success; error code in हाल of error
 */
पूर्णांक crypto_रेजिस्टर_scomp(काष्ठा scomp_alg *alg);

/**
 * crypto_unरेजिस्टर_scomp() -- Unरेजिस्टर synchronous compression algorithm
 *
 * Function unरेजिस्टरs an implementation of a synchronous
 * compression algorithm
 *
 * @alg:	algorithm definition
 */
व्योम crypto_unरेजिस्टर_scomp(काष्ठा scomp_alg *alg);

पूर्णांक crypto_रेजिस्टर_scomps(काष्ठा scomp_alg *algs, पूर्णांक count);
व्योम crypto_unरेजिस्टर_scomps(काष्ठा scomp_alg *algs, पूर्णांक count);

#पूर्ण_अगर
