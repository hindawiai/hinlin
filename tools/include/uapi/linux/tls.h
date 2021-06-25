<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _UAPI_LINUX_TLS_H
#घोषणा _UAPI_LINUX_TLS_H

#समावेश <linux/types.h>

/* TLS socket options */
#घोषणा TLS_TX			1	/* Set transmit parameters */
#घोषणा TLS_RX			2	/* Set receive parameters */

/* Supported versions */
#घोषणा TLS_VERSION_MINOR(ver)	((ver) & 0xFF)
#घोषणा TLS_VERSION_MAJOR(ver)	(((ver) >> 8) & 0xFF)

#घोषणा TLS_VERSION_NUMBER(id)	((((id##_VERSION_MAJOR) & 0xFF) << 8) |	\
				 ((id##_VERSION_MINOR) & 0xFF))

#घोषणा TLS_1_2_VERSION_MAJOR	0x3
#घोषणा TLS_1_2_VERSION_MINOR	0x3
#घोषणा TLS_1_2_VERSION		TLS_VERSION_NUMBER(TLS_1_2)

/* Supported ciphers */
#घोषणा TLS_CIPHER_AES_GCM_128				51
#घोषणा TLS_CIPHER_AES_GCM_128_IV_SIZE			8
#घोषणा TLS_CIPHER_AES_GCM_128_KEY_SIZE		16
#घोषणा TLS_CIPHER_AES_GCM_128_SALT_SIZE		4
#घोषणा TLS_CIPHER_AES_GCM_128_TAG_SIZE		16
#घोषणा TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE		8

#घोषणा TLS_SET_RECORD_TYPE	1
#घोषणा TLS_GET_RECORD_TYPE	2

काष्ठा tls_crypto_info अणु
	__u16 version;
	__u16 cipher_type;
पूर्ण;

काष्ठा tls12_crypto_info_aes_gcm_128 अणु
	काष्ठा tls_crypto_info info;
	अचिन्हित अक्षर iv[TLS_CIPHER_AES_GCM_128_IV_SIZE];
	अचिन्हित अक्षर key[TLS_CIPHER_AES_GCM_128_KEY_SIZE];
	अचिन्हित अक्षर salt[TLS_CIPHER_AES_GCM_128_SALT_SIZE];
	अचिन्हित अक्षर rec_seq[TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE];
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_TLS_H */
