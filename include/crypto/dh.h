<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Dअगरfie-Hellman secret to be used with kpp API aदीर्घ with helper functions
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_DH_
#घोषणा _CRYPTO_DH_

/**
 * DOC: DH Helper Functions
 *
 * To use DH with the KPP cipher API, the following data काष्ठाure and
 * functions should be used.
 *
 * To use DH with KPP, the following functions should be used to operate on
 * a DH निजी key. The packet निजी key that can be set with
 * the KPP API function call of crypto_kpp_set_secret.
 */

/**
 * काष्ठा dh - define a DH निजी key
 *
 * @key:	Private DH key
 * @p:		Dअगरfie-Hellman parameter P
 * @q:		Dअगरfie-Hellman parameter Q
 * @g:		Dअगरfie-Hellman generator G
 * @key_size:	Size of the निजी DH key
 * @p_size:	Size of DH parameter P
 * @q_size:	Size of DH parameter Q
 * @g_size:	Size of DH generator G
 */
काष्ठा dh अणु
	व्योम *key;
	व्योम *p;
	व्योम *q;
	व्योम *g;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक p_size;
	अचिन्हित पूर्णांक q_size;
	अचिन्हित पूर्णांक g_size;
पूर्ण;

/**
 * crypto_dh_key_len() - Obtain the size of the निजी DH key
 * @params:	निजी DH key
 *
 * This function वापसs the packet DH key size. A caller can use that
 * with the provided DH निजी key reference to obtain the required
 * memory size to hold a packet key.
 *
 * Return: size of the key in bytes
 */
अचिन्हित पूर्णांक crypto_dh_key_len(स्थिर काष्ठा dh *params);

/**
 * crypto_dh_encode_key() - encode the निजी key
 * @buf:	Buffer allocated by the caller to hold the packet DH
 *		निजी key. The buffer should be at least crypto_dh_key_len
 *		bytes in size.
 * @len:	Length of the packet निजी key buffer
 * @params:	Buffer with the caller-specअगरied निजी key
 *
 * The DH implementations operate on a packet representation of the निजी
 * key.
 *
 * Return:	-EINVAL अगर buffer has insufficient size, 0 on success
 */
पूर्णांक crypto_dh_encode_key(अक्षर *buf, अचिन्हित पूर्णांक len, स्थिर काष्ठा dh *params);

/**
 * crypto_dh_decode_key() - decode a निजी key
 * @buf:	Buffer holding a packet key that should be decoded
 * @len:	Length of the packet निजी key buffer
 * @params:	Buffer allocated by the caller that is filled with the
 *		unpacked DH निजी key.
 *
 * The unpacking obtains the निजी key by poपूर्णांकing @p to the correct location
 * in @buf. Thus, both poपूर्णांकers refer to the same memory.
 *
 * Return:	-EINVAL अगर buffer has insufficient size, 0 on success
 */
पूर्णांक crypto_dh_decode_key(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len, काष्ठा dh *params);

#पूर्ण_अगर
