<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM/SEC 4.x definitions क्रम handling key-generation jobs
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 */

/**
 * split_key_len - Compute MDHA split key length क्रम a given algorithm
 * @hash: Hashing algorithm selection, one of OP_ALG_ALGSEL_* - MD5, SHA1,
 *        SHA224, SHA384, SHA512.
 *
 * Return: MDHA split key length
 */
अटल अंतरभूत u32 split_key_len(u32 hash)
अणु
	/* Sizes क्रम MDHA pads (*not* keys): MD5, SHA1, 224, 256, 384, 512 */
	अटल स्थिर u8 mdpadlen[] = अणु 16, 20, 32, 32, 64, 64 पूर्ण;
	u32 idx;

	idx = (hash & OP_ALG_ALGSEL_SUBMASK) >> OP_ALG_ALGSEL_SHIFT;

	वापस (u32)(mdpadlen[idx] * 2);
पूर्ण

/**
 * split_key_pad_len - Compute MDHA split key pad length क्रम a given algorithm
 * @hash: Hashing algorithm selection, one of OP_ALG_ALGSEL_* - MD5, SHA1,
 *        SHA224, SHA384, SHA512.
 *
 * Return: MDHA split key pad length
 */
अटल अंतरभूत u32 split_key_pad_len(u32 hash)
अणु
	वापस ALIGN(split_key_len(hash), 16);
पूर्ण

काष्ठा split_key_result अणु
	काष्ठा completion completion;
	पूर्णांक err;
पूर्ण;

व्योम split_key_करोne(काष्ठा device *dev, u32 *desc, u32 err, व्योम *context);

पूर्णांक gen_split_key(काष्ठा device *jrdev, u8 *key_out,
		  काष्ठा alginfo * स्थिर adata, स्थिर u8 *key_in, u32 keylen,
		  पूर्णांक max_keylen);
