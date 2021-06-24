<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ECDH params to be used with kpp API
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */
#अगर_अघोषित _CRYPTO_ECDH_
#घोषणा _CRYPTO_ECDH_

/**
 * DOC: ECDH Helper Functions
 *
 * To use ECDH with the KPP cipher API, the following data काष्ठाure and
 * functions should be used.
 *
 * The ECC curves known to the ECDH implementation are specअगरied in this
 * header file.
 *
 * To use ECDH with KPP, the following functions should be used to operate on
 * an ECDH निजी key. The packet निजी key that can be set with
 * the KPP API function call of crypto_kpp_set_secret.
 */

/* Curves IDs */
#घोषणा ECC_CURVE_NIST_P192	0x0001
#घोषणा ECC_CURVE_NIST_P256	0x0002
#घोषणा ECC_CURVE_NIST_P384	0x0003

/**
 * काष्ठा ecdh - define an ECDH निजी key
 *
 * @key:	Private ECDH key
 * @key_size:	Size of the निजी ECDH key
 */
काष्ठा ecdh अणु
	अक्षर *key;
	अचिन्हित लघु key_size;
पूर्ण;

/**
 * crypto_ecdh_key_len() - Obtain the size of the निजी ECDH key
 * @params:	निजी ECDH key
 *
 * This function वापसs the packet ECDH key size. A caller can use that
 * with the provided ECDH निजी key reference to obtain the required
 * memory size to hold a packet key.
 *
 * Return: size of the key in bytes
 */
अचिन्हित पूर्णांक crypto_ecdh_key_len(स्थिर काष्ठा ecdh *params);

/**
 * crypto_ecdh_encode_key() - encode the निजी key
 * @buf:	Buffer allocated by the caller to hold the packet ECDH
 *		निजी key. The buffer should be at least crypto_ecdh_key_len
 *		bytes in size.
 * @len:	Length of the packet निजी key buffer
 * @p:		Buffer with the caller-specअगरied निजी key
 *
 * The ECDH implementations operate on a packet representation of the निजी
 * key.
 *
 * Return:	-EINVAL अगर buffer has insufficient size, 0 on success
 */
पूर्णांक crypto_ecdh_encode_key(अक्षर *buf, अचिन्हित पूर्णांक len, स्थिर काष्ठा ecdh *p);

/**
 * crypto_ecdh_decode_key() - decode a निजी key
 * @buf:	Buffer holding a packet key that should be decoded
 * @len:	Length of the packet निजी key buffer
 * @p:		Buffer allocated by the caller that is filled with the
 *		unpacked ECDH निजी key.
 *
 * The unpacking obtains the निजी key by poपूर्णांकing @p to the correct location
 * in @buf. Thus, both poपूर्णांकers refer to the same memory.
 *
 * Return:	-EINVAL अगर buffer has insufficient size, 0 on success
 */
पूर्णांक crypto_ecdh_decode_key(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len, काष्ठा ecdh *p);

#पूर्ण_अगर
