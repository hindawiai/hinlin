<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hash Info: Hash algorithms inक्रमmation
 *
 * Copyright (c) 2013 Dmitry Kasatkin <d.kasatkin@samsung.com>
 */

#अगर_अघोषित _CRYPTO_HASH_INFO_H
#घोषणा _CRYPTO_HASH_INFO_H

#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/streebog.h>

#समावेश <uapi/linux/hash_info.h>

/* not defined in include/crypto/ */
#घोषणा RMD128_DIGEST_SIZE      16
#घोषणा RMD160_DIGEST_SIZE	20
#घोषणा RMD256_DIGEST_SIZE      32
#घोषणा RMD320_DIGEST_SIZE      40

/* not defined in include/crypto/ */
#घोषणा WP512_DIGEST_SIZE	64
#घोषणा WP384_DIGEST_SIZE	48
#घोषणा WP256_DIGEST_SIZE	32

/* not defined in include/crypto/ */
#घोषणा TGR128_DIGEST_SIZE 16
#घोषणा TGR160_DIGEST_SIZE 20
#घोषणा TGR192_DIGEST_SIZE 24

/* not defined in include/crypto/ */
#घोषणा SM3256_DIGEST_SIZE 32

बाह्य स्थिर अक्षर *स्थिर hash_algo_name[HASH_ALGO__LAST];
बाह्य स्थिर पूर्णांक hash_digest_size[HASH_ALGO__LAST];

#पूर्ण_अगर /* _CRYPTO_HASH_INFO_H */
